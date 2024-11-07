#pragma once
#include <d3d11.h>

class DeviceContext;

class SwapChain
{
public:
	SwapChain();
	~SwapChain();

	bool init(HWND hwnd, UINT width, UINT height);
	bool present(bool vsync);
	bool release();
	
	ID3D11ShaderResourceView* m_offscreen_srv;

private:
	IDXGISwapChain* m_swap_chain;
	ID3D11RenderTargetView* m_rtv;
	ID3D11DepthStencilView* m_dsv;
	ID3D11Texture2D* m_depth_stencil_texture;
	ID3D11RenderTargetView* m_offscreen_rtv;
	ID3D11Texture2D* m_offscreen_texture;
	ID3D11SamplerState* m_sampler_state;

	friend class DeviceContext;
};

