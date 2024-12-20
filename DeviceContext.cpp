#include "DeviceContext.h"
#include "SwapChain.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "Texture.h"

#include <exception>

DeviceContext::DeviceContext(RenderSystem* system, ID3D11DeviceContext* device_context) : m_system(system), m_device_context(device_context) {}

DeviceContext::~DeviceContext() 
{
	if(m_device_context) m_device_context->Release();
}

ID3D11DeviceContext* DeviceContext::getContext()
{
    return this->m_device_context;
}

void DeviceContext::clearRenderTargetColor(const SwapChainPtr& swap_chain, float red, float green, float blue, float alpha)
{
	FLOAT clear_color[] = { red,green,blue,alpha };
	m_device_context->ClearRenderTargetView(swap_chain->m_rtv, clear_color);
	m_device_context->ClearDepthStencilView(swap_chain->m_dsv, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1, 0);
	m_device_context->OMSetRenderTargets(1, &swap_chain->m_rtv, swap_chain->m_dsv);
}

void DeviceContext::setVertexBuffer(VertexBufferPtr vertex_buffer)
{
	UINT stride = vertex_buffer->m_size_vertex;
	UINT offset = 0;

	m_device_context->IASetVertexBuffers(0, 1, &vertex_buffer->m_buffer, &stride, &offset);
	m_device_context->IASetInputLayout(vertex_buffer->m_layout);
}

void DeviceContext::setIndexBuffer(IndexBufferPtr index_buffer)
{
	m_device_context->IASetIndexBuffer(index_buffer->m_buffer, DXGI_FORMAT_R32_UINT, 0);
}
	
void DeviceContext::setVertexShader(VertexShaderPtr vertex_shader)
{
	m_device_context->VSSetShader(vertex_shader->m_vs, nullptr, 0);
}

void DeviceContext::setPixelShader(PixelShaderPtr pixel_shader)
{
	m_device_context->PSSetShader(pixel_shader->m_ps, nullptr, 0);
}

void DeviceContext::setConstantBuffer(ConstantBufferPtr buffer)
{
	m_device_context->VSSetConstantBuffers(0, 1, &buffer->m_buffer);
    m_device_context->PSSetConstantBuffers(0, 1, &buffer->m_buffer);
}

void DeviceContext::setTexture(TexturePtr texture)
{
    m_device_context->VSSetShaderResources(0, 1, &texture->m_shader_resource_view);
    m_device_context->PSSetShaderResources(0, 1, &texture->m_shader_resource_view);
}

void DeviceContext::drawTriangleList(UINT vertex_count, UINT start_vertex_index)
{
	m_device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    m_device_context->Draw(vertex_count, start_vertex_index);
}

void DeviceContext::drawIndexedTriangle(UINT index_count, UINT start_vertex_index, UINT start_index_location)
{
	m_device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_device_context->DrawIndexed(index_count, start_index_location, start_vertex_index);
}

void DeviceContext::drawLineList(UINT vertex_count, UINT start_vertex_index)
{
	m_device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
	m_device_context->Draw(vertex_count, start_vertex_index);
}

void DeviceContext::drawIndexedLine(UINT index_count, UINT start_vertex_index, UINT start_index_location)
{
	m_device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
	m_device_context->DrawIndexed(index_count, start_index_location, start_vertex_index);
}

void DeviceContext::drawPointList(UINT vertex_count, UINT start_vertex_index)
{
	m_device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
	m_device_context->Draw(vertex_count, start_vertex_index);
}

void DeviceContext::drawIndexedPoint(UINT index_count, UINT start_vertex_index, UINT start_index_location)
{
	m_device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
	m_device_context->DrawIndexed(index_count, start_index_location, start_vertex_index);
}

void DeviceContext::setViewportSize(UINT width, UINT height)
{
	D3D11_VIEWPORT vp = {};
	vp.Width = (FLOAT)width;
	vp.Height = (FLOAT)height;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	m_device_context->RSSetViewports(1, &vp);
}
