#include "..\..\Header\DirectX\Dx12RenderTarget.h"
#include "..\..\Header\DirectX\Dx12Wrapper.h"
#include "..\..\Header\DirectX\COMRelease.h"

GatesEngine::MyDirectX::Dx12RenderTarget::Dx12RenderTarget() :dx12Wrapper(nullptr), rtvHeap(nullptr)
{
}

GatesEngine::MyDirectX::Dx12RenderTarget::~Dx12RenderTarget()
{
	COM_RELEASE(rtvHeap);
}

ID3D12DescriptorHeap * GatesEngine::MyDirectX::Dx12RenderTarget::GetHeap()
{
	return rtvHeap;
}

bool GatesEngine::MyDirectX::Dx12RenderTarget::Create(Dx12Wrapper* wrapper, std::vector<ID3D12Resource*>* resources)
{
	pResources.resize((int)(*resources).size());
	//ヒープの生成
	HRESULT result;
	D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc = {};
	rtvHeapDesc.NumDescriptors = (int)(*resources).size();
	rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	result = wrapper->GetDevice()->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(&rtvHeap));
	//ビューの生成
	D3D12_RENDER_TARGET_VIEW_DESC rtvDesc = {};
	rtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	rtvDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;

	int i = 0;
	for (auto& r : *resources)
	{
		D3D12_CPU_DESCRIPTOR_HANDLE rtvHeapHandle = rtvHeap->GetCPUDescriptorHandleForHeapStart();
		rtvHeapHandle.ptr += i * wrapper->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
		wrapper->GetDevice()->CreateRenderTargetView((*resources)[i], &rtvDesc, rtvHeapHandle);
		pResources[i] = (*resources)[i];
		++i;
	}
	dx12Wrapper = wrapper;
	return false;
}

bool GatesEngine::MyDirectX::Dx12RenderTarget::Create(Dx12Wrapper * wrapper, ID3D12Resource * resource)
{
	pResources.resize(1);
	//ヒープの生成
	HRESULT result;
	D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc = {};
	rtvHeapDesc.NumDescriptors = 1;
	rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	result = wrapper->GetDevice()->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(&rtvHeap));
	//ビューの生成
	D3D12_RENDER_TARGET_VIEW_DESC rtvDesc = {};
	rtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	rtvDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;

	D3D12_CPU_DESCRIPTOR_HANDLE rtvHeapHandle = rtvHeap->GetCPUDescriptorHandleForHeapStart();
	wrapper->GetDevice()->CreateRenderTargetView(resource, &rtvDesc, rtvHeapHandle);
	pResources[0] = resource;
	dx12Wrapper = wrapper;
	return false;
}
