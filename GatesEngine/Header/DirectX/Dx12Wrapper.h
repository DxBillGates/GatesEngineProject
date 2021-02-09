#pragma once
#include "..\Math\Vector4.h"
#include "Dx12RenderTarget.h"
#include <d3d12.h>
#include <dxgi1_6.h>
#include <vector>
namespace GatesEngine
{
	namespace MyDirectX
	{
		//DirectX12のリソース生成の補助やアプリケーションに人るだけあればいいID3D12オブジェクトなどを保持
		//自作DirectX関連のクラスはこのクラスをポインタで保持する予定
		class Dx12Wrapper
		{
		private:
			using Vector4 = GatesEngine::Math::Vector4;
		private:
			D3D12_VIEWPORT               mViewport;
			D3D12_RECT                   mRect;
			IDXGIFactory6*               mDxgiFactory;
			std::vector<IDXGIAdapter*>   mEnumAdapter;
			IDXGIAdapter*                mUseAdapter;
			ID3D12Device*                mDevice;
			ID3D12CommandAllocator*      mCmdAlloc;
			ID3D12GraphicsCommandList*   mCmdList;
			ID3D12CommandQueue*          mCmdQueue;
			IDXGISwapChain4*             mSwapChain;
			std::vector<ID3D12Resource*> mFrameBuffer;
			Dx12RenderTarget*            mRenderTarget;
			ID3D12DescriptorHeap*        mDsvHeap;
			ID3D12Resource*              mDepthBuffer;
			ID3D12Fence*                 mFence;
			UINT64                       mFenceValue;
		protected:
			void SetViewport(int wndWidth, int wndHeight);
			void CreateDxgiFactory();
			void CreateDevice();
			void CreateCmdList();
			void CreateSwapChain(HWND hwnd);
			void CreateRtv();
			void CreateDsv();
			void CreateFence();
		public:
			Dx12Wrapper(HWND hwnd, int wndWidth, int wndHeight);
			~Dx12Wrapper();
			void SetRenderTarget(Vector4 color, Dx12RenderTarget* useRenderTarget = nullptr);
			void ScreenFlip();
			void ClearDepthStencilView();
			void SetResourceBarrier(ID3D12Resource* resource, D3D12_RESOURCE_STATES before, D3D12_RESOURCE_STATES after);
			ID3D12Device* GetDevice();
			ID3D12GraphicsCommandList* GetCmdList();
			IDXGISwapChain4* GetSwapChain();
			ID3D12Resource* GetCurrentFrameBuffer();
			ID3D12DescriptorHeap* GetRtvHeap();
		};
	}
}
