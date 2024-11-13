#pragma once
#include <d3d11.h>
#include "Prerequisites.h"

class VertexBuffer
{
public:
	VertexBuffer(void* list_vertices, UINT size_vertex, UINT size_list, void* shader_byte_code, size_t size_byte_shader, RenderSystem* system);
	~VertexBuffer();

	UINT getSizeVertexList();

private:
	UINT m_size_vertex = 0;
	UINT m_size_list = 0;

	ID3D11Buffer* m_buffer = nullptr;
	ID3D11InputLayout* m_layout = nullptr;
	RenderSystem* m_system = nullptr;

	friend class DeviceContext;
};

