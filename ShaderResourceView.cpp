#include "ShaderResourceView.h"
#include "GraphicsEngine.h"

ShaderResourceView::ShaderResourceView() {}

ShaderResourceView::~ShaderResourceView() {}

void ShaderResourceView::release()
{
	m_srv->Release();
	delete this;
}

bool ShaderResourceView::init(ID3D11Resource* resource, const D3D11_SHADER_RESOURCE_VIEW_DESC* srvDesc = nullptr)
{
	if (!resource) {
		return false;
	}

	if (!SUCCEEDED(GraphicsEngine::getInstance()->m_d3d_device->CreateShaderResourceView(resource, srvDesc, &m_srv)))
	{
		return false;
	}

	return true;
}
