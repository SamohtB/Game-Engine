#include "SwapChain.h"
#include "GraphicsEngine.h"
#include <exception>

SwapChain::SwapChain() {}

bool SwapChain::init(HWND hwnd, UINT width, UINT height)
{
	ID3D11Device* device = GraphicsEngine::getInstance()->m_d3d_device;

	DXGI_SWAP_CHAIN_DESC desc = {};
	desc.BufferCount = 1;
	desc.BufferDesc.Width = width;
	desc.BufferDesc.Height = height;
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.BufferDesc.RefreshRate.Numerator = 60;
	desc.BufferDesc.RefreshRate.Denominator = 1;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.OutputWindow = hwnd;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Windowed = TRUE;

	HRESULT hr = GraphicsEngine::getInstance()->m_dxgi_factory->CreateSwapChain(device, &desc, &m_swap_chain);

	if (FAILED(hr))
	{
		return false;
	}

	ID3D11Texture2D* backBuffer;
	hr = m_swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);

	if (FAILED(hr))
	{
		return false;
	}

	hr = device->CreateRenderTargetView(backBuffer, nullptr, &m_rtv);

	if (FAILED(hr))
	{
		return false;
	}
	/* Depth Stencil */
	D3D11_TEXTURE2D_DESC depthStencilDesc = {};
	depthStencilDesc.Width = width;
	depthStencilDesc.Height = height;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilDesc.SampleDesc.Count = 1;
	depthStencilDesc.SampleDesc.Quality = 0;
	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = 0;
	depthStencilDesc.MiscFlags = 0;

	hr = device->CreateTexture2D(&depthStencilDesc, nullptr, &m_rtt);

	if (FAILED(hr))
	{
		throw std::exception("Depth Stencil Texture not Created Successfully");
	}

	hr = device->CreateDepthStencilView(m_rtt, nullptr, &m_dsv);

	if (FAILED(hr))
	{
		throw std::exception("Depth Stencil View not Created Successfully");
	}

	/* Offscreen Render Target Texture */
	D3D11_TEXTURE2D_DESC renderTargetDesc = {};
	renderTargetDesc.Width = width;
	renderTargetDesc.Height = height;
	renderTargetDesc.MipLevels = 1;
	renderTargetDesc.ArraySize = 1;
	renderTargetDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	renderTargetDesc.SampleDesc.Count = 1;
	renderTargetDesc.Usage = D3D11_USAGE_DEFAULT;
	renderTargetDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;

	hr = device->CreateTexture2D(&renderTargetDesc, nullptr, &m_rtt);

	if (FAILED(hr))
	{
		return false;
	}

	hr = device->CreateRenderTargetView(m_rtt, nullptr, &m_offscreen_rtv);

	if (FAILED(hr))
	{
		return false;
	}

	hr = device->CreateShaderResourceView(m_rtt, nullptr, &m_offscreen_srv);

	if (FAILED(hr))
	{
		return false;
	}

	return true;
}

bool SwapChain::present(bool vsync)
{
	m_swap_chain->Present(vsync, NULL);

	return true;
}

bool SwapChain::release()
{
	m_swap_chain->Release();
	m_rtv->Release();
	m_dsv->Release();
	m_rtt->Release();
	m_offscreen_rtv->Release();
	m_offscreen_srv->Release();
	delete this;
	return true;
}

SwapChain::~SwapChain()
{
}