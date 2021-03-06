#include "..\..\Header\DirectX\Dx12Wrapper.h"
#include "..\..\Header\DirectX\COMRelease.h"
#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")
GatesEngine::MyDirectX::Dx12Wrapper::Dx12Wrapper(HWND hwnd, int wndWidth, int wndHeight)
	:mViewport({}), mRect({}), mDxgiFactory(nullptr), mEnumAdapter(std::vector<IDXGIAdapter*>()), mUseAdapter(nullptr),
	mDevice(nullptr), mCmdAlloc(nullptr), mCmdList(nullptr), mCmdQueue(nullptr), mSwapChain(nullptr),
	mFrameBuffer(std::vector<ID3D12Resource*>()),mRenderTarget(nullptr), mDsvHeap(nullptr), mDepthBuffer(nullptr),
	mFence(nullptr), mFenceValue(0)
{
#ifdef _DEBUG
	HRESULT result;
	ID3D12Debug* debug;
	if (SUCCEEDED(result = D3D12GetDebugInterface(IID_PPV_ARGS(&debug))))
	{
		debug->EnableDebugLayer();
		COM_RELEASE(debug);
	}
#endif
	SetViewport(wndWidth, wndHeight);
	CreateDxgiFactory();
	CreateDevice();
	CreateCmdList();
	CreateSwapChain(hwnd);
	CreateRtv();
	CreateDsv();
	CreateFence();
}

GatesEngine::MyDirectX::Dx12Wrapper::~Dx12Wrapper()
{
	//実行中のコマンドが終了してから解放!!
	mCmdQueue->Signal(mFence, ++mFenceValue);
	if (mFence->GetCompletedValue() != mFenceValue)
	{
		HANDLE event = CreateEvent(nullptr, false, false, nullptr);
		mFence->SetEventOnCompletion(mFenceValue, event);
		WaitForSingleObject(event, INFINITE);
		CloseHandle(event);
	}
	COM_RELEASE(mDxgiFactory);
	COM_RELEASE(mDevice);
	COM_RELEASE(mCmdAlloc);
	COM_RELEASE(mCmdList);
	COM_RELEASE(mCmdQueue);
	COM_RELEASE(mFrameBuffer[0]);
	COM_RELEASE(mFrameBuffer[1]);
	COM_RELEASE(mSwapChain);
	delete mRenderTarget;
	COM_RELEASE(mDepthBuffer);
	COM_RELEASE(mDsvHeap);
	COM_RELEASE(mFence);
}

void GatesEngine::MyDirectX::Dx12Wrapper::SetRenderTarget(Vector4 color, Dx12RenderTarget * useRenderTarget)
{
	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle;
	D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle;

	//useRenderTargetがnullptrの場合はバックバッファをレンダ―ターゲットとするかつ深度情報を初期化する
	if (useRenderTarget == nullptr)
	{
		useRenderTarget = mRenderTarget;
		SetResourceBarrier(mFrameBuffer[mSwapChain->GetCurrentBackBufferIndex()], D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);
		rtvHandle = useRenderTarget->GetHeap()->GetCPUDescriptorHandleForHeapStart();
		rtvHandle.ptr += mSwapChain->GetCurrentBackBufferIndex() * mDevice->GetDescriptorHandleIncrementSize(useRenderTarget->GetHeap()->GetDesc().Type);
		dsvHandle = mDsvHeap->GetCPUDescriptorHandleForHeapStart();
		mCmdList->OMSetRenderTargets(1, &rtvHandle, false, &dsvHandle);
		ClearDepthStencilView();
	}
	else
	{
		useRenderTarget->Prepare();
		rtvHandle = useRenderTarget->GetHeap()->GetCPUDescriptorHandleForHeapStart();
		mCmdList->OMSetRenderTargets(1, &rtvHandle, false, nullptr);
	}
	//useRenderTargetをcolorで塗りつぶす
	float rgba[] = { color.x,color.y,color.z,color.w };
	mCmdList->ClearRenderTargetView(rtvHandle, rgba, 0, nullptr);

	mCmdList->RSSetViewports(1, &mViewport);
	mCmdList->RSSetScissorRects(1, &mRect);
	mCmdList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void GatesEngine::MyDirectX::Dx12Wrapper::ScreenFlip()
{
	SetResourceBarrier(mFrameBuffer[mSwapChain->GetCurrentBackBufferIndex()],D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT);
	mCmdList->Close();
	ID3D12CommandList* cmdLists[] = { mCmdList };
	mCmdQueue->ExecuteCommandLists(1, cmdLists);
	mCmdQueue->Signal(mFence, ++mFenceValue);
	if (mFence->GetCompletedValue() != mFenceValue)
	{
		HANDLE event = CreateEvent(nullptr, false, false, nullptr);
		mFence->SetEventOnCompletion(mFenceValue, event);
		WaitForSingleObject(event, INFINITE);
		CloseHandle(event);
	}
	mCmdAlloc->Reset();
	mCmdList->Reset(mCmdAlloc, nullptr);
	mSwapChain->Present(0, 0);
}

void GatesEngine::MyDirectX::Dx12Wrapper::ClearDepthStencilView()
{
	D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle = mDsvHeap->GetCPUDescriptorHandleForHeapStart();
	mCmdList->ClearDepthStencilView(dsvHandle, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);
}

void GatesEngine::MyDirectX::Dx12Wrapper::SetResourceBarrier(ID3D12Resource * resource, D3D12_RESOURCE_STATES before, D3D12_RESOURCE_STATES after)
{
	D3D12_RESOURCE_BARRIER barrier = {};
	barrier.Transition.pResource = resource;
	barrier.Transition.StateAfter = after;
	barrier.Transition.StateBefore = before;
	mCmdList->ResourceBarrier(1, &barrier);
}

ID3D12Device * GatesEngine::MyDirectX::Dx12Wrapper::GetDevice()
{
	return mDevice;
}

ID3D12GraphicsCommandList * GatesEngine::MyDirectX::Dx12Wrapper::GetCmdList()
{
	return mCmdList;
}

IDXGISwapChain4 * GatesEngine::MyDirectX::Dx12Wrapper::GetSwapChain()
{
	return mSwapChain;
}

ID3D12Resource * GatesEngine::MyDirectX::Dx12Wrapper::GetCurrentFrameBuffer()
{
	return mFrameBuffer[mSwapChain->GetCurrentBackBufferIndex()];
}

ID3D12DescriptorHeap * GatesEngine::MyDirectX::Dx12Wrapper::GetRtvHeap()
{
	return nullptr;
}

void GatesEngine::MyDirectX::Dx12Wrapper::SetViewport(int wndWidth, int wndHeight)
{
	mViewport = { 0,0,(float)wndWidth,(float)wndHeight,0,1.0f };
	mRect = { 0,0,wndWidth,wndHeight };
}

void GatesEngine::MyDirectX::Dx12Wrapper::CreateDxgiFactory()
{
	//DXGIFactoryの生成
	HRESULT result;
	result = CreateDXGIFactory(IID_PPV_ARGS(&mDxgiFactory));
}

void GatesEngine::MyDirectX::Dx12Wrapper::CreateDevice()
{
	//使用できるGPUを探してそのアダプタでID3DDeviceを生成
	HRESULT result;
	for (int i = 0; mDxgiFactory->EnumAdapters(i, &mUseAdapter) != DXGI_ERROR_NOT_FOUND; ++i)
	{
		mEnumAdapter.push_back(mUseAdapter);
	}
	DXGI_ADAPTER_DESC adapterDesc = {};
	for (int i = 0; i < (int)mEnumAdapter.size(); ++i)
	{
		mEnumAdapter[i]->GetDesc(&adapterDesc);
		std::wstring adapterName = adapterDesc.Description;
		if (adapterName.find(L"Microsoft") == std::wstring::npos && adapterName.find(L"Intel") == std::wstring::npos)
		{
			mUseAdapter = mEnumAdapter[i];
			break;
		}
	}
	D3D_FEATURE_LEVEL featureLevel[] = { D3D_FEATURE_LEVEL_12_1, D3D_FEATURE_LEVEL_12_0, D3D_FEATURE_LEVEL_11_1, D3D_FEATURE_LEVEL_11_0 };
	for (int i = 0; i < _countof(featureLevel); ++i)
	{
		if (SUCCEEDED(result = D3D12CreateDevice(mUseAdapter, featureLevel[i], IID_PPV_ARGS(&mDevice))))break;
	}
}

void GatesEngine::MyDirectX::Dx12Wrapper::CreateCmdList()
{
	//コマンド関係を生成
	HRESULT result;
	result = mDevice->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&mCmdAlloc));
	result = mDevice->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, mCmdAlloc, nullptr, IID_PPV_ARGS(&mCmdList));
	D3D12_COMMAND_QUEUE_DESC cmdQueueDesc = {};
	result = mDevice->CreateCommandQueue(&cmdQueueDesc, IID_PPV_ARGS(&mCmdQueue));
}

void GatesEngine::MyDirectX::Dx12Wrapper::CreateSwapChain(HWND hwnd)
{
	//ApplicationからgameWindowのハンドルを取得しそのハンドルとそのほかの設定からSwapChainを生成
	HRESULT result;
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
	swapChainDesc.Width = (UINT)mViewport.Width;
	swapChainDesc.Height = (UINT)mViewport.Height;
	swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.BufferUsage = DXGI_USAGE_BACK_BUFFER;
	swapChainDesc.BufferCount = 2;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	result = mDxgiFactory->CreateSwapChainForHwnd(mCmdQueue, hwnd, &swapChainDesc, nullptr, nullptr, (IDXGISwapChain1**)&mSwapChain);
}

void GatesEngine::MyDirectX::Dx12Wrapper::CreateRtv()
{
	//mRenderTarget = new MyDirectX::Dx12RenderTarget(this, 2);
	HRESULT result;
	//mFrameBuffer.resize(2);
	//D3D12_RENDER_TARGET_VIEW_DESC rtvDesc = {};
	//rtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	//rtvDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;
	////SwapChainからバックバッファ、フロントバッファを取得しそれをもとにRTVを生成
	//for (int i = 0; i < (int)mFrameBuffer.size(); ++i)
	//{
	//	result = mSwapChain->GetBuffer(i, IID_PPV_ARGS(&mFrameBuffer[i]));
	//	D3D12_CPU_DESCRIPTOR_HANDLE rtvHeapHandle = mRenderTarget->GetHeap()->GetCPUDescriptorHandleForHeapStart();
	//	rtvHeapHandle.ptr += i * mDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	//	mDevice->CreateRenderTargetView(mFrameBuffer[i], &rtvDesc, rtvHeapHandle);
	//}

	mRenderTarget = new MyDirectX::Dx12RenderTarget();
	mFrameBuffer.resize(2);
	for (int i = 0; i < (int)mFrameBuffer.size(); ++i)
	{
		result = mSwapChain->GetBuffer(i, IID_PPV_ARGS(&mFrameBuffer[i]));
	}

	mRenderTarget->Create(this, &mFrameBuffer);
}

void GatesEngine::MyDirectX::Dx12Wrapper::CreateDsv()
{
	//デプスバッファの設定
	HRESULT result;
	D3D12_HEAP_PROPERTIES heapProp = {};
	heapProp.Type = D3D12_HEAP_TYPE_DEFAULT;
	D3D12_RESOURCE_DESC resDesc = {};
	resDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	resDesc.Width = (UINT64)mViewport.Width;
	resDesc.Height = (UINT64)mViewport.Height;
	resDesc.DepthOrArraySize = 1;
	resDesc.Format = DXGI_FORMAT_D32_FLOAT;
	resDesc.SampleDesc.Count = 1;
	resDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;
	//デプスバッファのフォーマットと最大深度値を設定
	D3D12_CLEAR_VALUE depthClearValue = {};
	depthClearValue.DepthStencil.Depth = 1.0f;
	depthClearValue.Format = DXGI_FORMAT_D32_FLOAT;
	//設定をもとにデプスバッファを生成
	result = mDevice->CreateCommittedResource(&heapProp, D3D12_HEAP_FLAG_NONE, &resDesc, D3D12_RESOURCE_STATE_DEPTH_WRITE, &depthClearValue, IID_PPV_ARGS(&mDepthBuffer));
	//DSVを格納するためのヒープの設定
	D3D12_DESCRIPTOR_HEAP_DESC dsvHeapDesc = {};
	dsvHeapDesc.NumDescriptors = 1;
	dsvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
	//DSVヒープの生成
	result = mDevice->CreateDescriptorHeap(&dsvHeapDesc, IID_PPV_ARGS(&mDsvHeap));
	//DSVの生成
	D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
	dsvDesc.Format = resDesc.Format;
	dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
	mDevice->CreateDepthStencilView(mDepthBuffer, &dsvDesc, mDsvHeap->GetCPUDescriptorHandleForHeapStart());
}

void GatesEngine::MyDirectX::Dx12Wrapper::CreateFence()
{
	//CPUとGPUの同期をさせる役割を持つフェンスを生成
	HRESULT result;
	result = mDevice->CreateFence(mFenceValue, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&mFence));
}
