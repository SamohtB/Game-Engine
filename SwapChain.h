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
	
private:
	IDXGISwapChain* m_swap_chain = 0;
	ID3D11RenderTargetView* m_rtv = nullptr;
	ID3D11DepthStencilView* m_dsv = nullptr;
	ID3D11Texture2D* m_rtt = nullptr;
	ID3D11ShaderResourceView* m_srv = nullptr;


	friend class DeviceContext;
};

