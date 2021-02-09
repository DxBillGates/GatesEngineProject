#include "..\..\Header\DirectX\Dx12RenderTarget.h"
#include "..\..\Header\DirectX\Dx12Wrapper.h"
#include "..\..\Header\DirectX\COMRelease.h"

GatesEngine::MyDirectX::Dx12RenderTarget::Dx12RenderTarget(Dx12Wrapper* dxWrapper, int numRtv):dx12Wrapper(dxWrapper),rtvHeap(nullptr)
{
	//RTV‚ðŠi”[‚·‚é‚½‚ß‚Ìƒq[ƒv‚ð¶¬
	HRESULT result;
	D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc = {};
	rtvHeapDesc.NumDescriptors = 2;
	rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	result = dx12Wrapper->GetDevice()->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(&rtvHeap));
}

GatesEngine::MyDirectX::Dx12RenderTarget::~Dx12RenderTarget()
{
	COM_RELEASE(rtvHeap);
}

ID3D12DescriptorHeap * GatesEngine::MyDirectX::Dx12RenderTarget::GetHeap()
{
	return rtvHeap;
}
