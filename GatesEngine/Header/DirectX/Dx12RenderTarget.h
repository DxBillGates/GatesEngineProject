#pragma once
#include <d3d12.h>
namespace GatesEngine
{
	namespace MyDirectX
	{
		class Dx12Wrapper;
		class Dx12RenderTarget
		{
		private:
			Dx12Wrapper* dx12Wrapper;
			ID3D12DescriptorHeap* rtvHeap;
		public:
			Dx12RenderTarget(Dx12Wrapper* dxWrapper, int numRtv);
			virtual ~Dx12RenderTarget();
			ID3D12DescriptorHeap* GetHeap();
			virtual void Prepare() {};
		};
	}
}
