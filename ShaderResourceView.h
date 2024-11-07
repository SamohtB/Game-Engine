#pragma once
#include <d3d11.h>

class GraphicsEngine;
class DeviceContext;

class ShaderResourceView
{
public:
	ShaderResourceView();
	~ShaderResourceView();

	void release();

private:
	bool init(ID3D11Resource* resource, const D3D11_SHADER_RESOURCE_VIEW_DESC* srvDesc = nullptr);

	ID3D11ShaderResourceView* m_srv = nullptr;

	friend class GraphicsEngine;
	friend class DeviceContext;
};