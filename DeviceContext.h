#pragma once
#include <d3d11.h>

class SwapChain;
class VertexBuffer;
class IndexBuffer;
class ConstantBuffer;
class VertexShader;
class PixelShader;

class DeviceContext
{
public:
	DeviceContext(ID3D11DeviceContext* device_context);
	~DeviceContext();

	void clearRenderTargetColor(SwapChain* swap_chain, float red, float green, float blue, float alpha);
	void clearRenderTargetColor2(SwapChain* swap_chain, float red, float green, float blue, float alpha);
	void setVertexBuffer(VertexBuffer* vertex_buffer);
	void setIndexBuffer(IndexBuffer* index_buffer);
	void setViewportSize(UINT width, UINT height);

	void setVertexShader(VertexShader* vertex_shader);
	void setPixelShader(PixelShader* pixel_shader);

	void setPixelShaderResources(ID3D11ShaderResourceView* shader_resource_view);

	void setConstantBuffer(VertexShader* vertex_shader, ConstantBuffer* buffer);
	void setConstantBuffer(PixelShader* pixel_shader, ConstantBuffer* buffer);

	void drawTriangleList(UINT vertex_count, UINT start_vertex_index);
	void drawIndexedTriangle(UINT index_count, UINT start_vertex_index, UINT start_index_location);

	void drawLineList(UINT vertex_count, UINT start_vertex_index);
	void drawIndexedLine(UINT index_count, UINT start_vertex_index, UINT start_index_location);

	void drawPointList(UINT vertex_count, UINT start_vertex_index);
	void drawIndexedPoint(UINT index_count, UINT start_vertex_index, UINT start_index_location);

	bool release();
	
private:
	ID3D11DeviceContext* m_device_context;
	D3D11_PRIMITIVE_TOPOLOGY current_topology = D3D_PRIMITIVE_TOPOLOGY_UNDEFINED;

	friend class ConstantBuffer;
};

