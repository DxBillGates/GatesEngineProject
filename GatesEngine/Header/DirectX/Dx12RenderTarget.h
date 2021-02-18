#pragma once
#include <vector>
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
			std::vector<ID3D12Resource*> pResources;
		public:
			Dx12RenderTarget();
			virtual ~Dx12RenderTarget();
			ID3D12DescriptorHeap* GetHeap();
			bool Create(Dx12Wrapper* wrapper,std::vector<ID3D12Resource*>* resources);
			bool Create(Dx12Wrapper* wrapper, ID3D12Resource* resource);
			virtual void Prepare() {};
		};
	}
}
