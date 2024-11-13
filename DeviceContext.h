#pragma once
#include <d3d11.h>
#include "Prerequisites.h"

class DeviceContext
{
public:
	DeviceContext(RenderSystem* system, ID3D11DeviceContext* device_context);
	~DeviceContext();

	void clearRenderTargetColor(SwapChainPtr swap_chain, float red, float green, float blue, float alpha);
	void setVertexBuffer(VertexBufferPtr vertex_buffer);
	void setIndexBuffer(IndexBufferPtr index_buffer);
	void setViewportSize(UINT width, UINT height);

	void setVertexShader(VertexShaderPtr vertex_shader);
	void setPixelShader(PixelShaderPtr pixel_shader);

	void setConstantBuffer(VertexShaderPtr vertex_shader, ConstantBufferPtr buffer);
	void setConstantBuffer(PixelShaderPtr pixel_shader, ConstantBufferPtr buffer);

	void drawTriangleList(UINT vertex_count, UINT start_vertex_index);
	void drawIndexedTriangle(UINT index_count, UINT start_vertex_index, UINT start_index_location);

	void drawLineList(UINT vertex_count, UINT start_vertex_index);
	void drawIndexedLine(UINT index_count, UINT start_vertex_index, UINT start_index_location);

	void drawPointList(UINT vertex_count, UINT start_vertex_index);
	void drawIndexedPoint(UINT index_count, UINT start_vertex_index, UINT start_index_location);
	
private:
	ID3D11DeviceContext* m_device_context;

	RenderSystem* m_system = nullptr;

	friend class ConstantBuffer;
};

