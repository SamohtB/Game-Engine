#include "Mesh.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>
#include <locale>
#include <filesystem>
#include <DirectXMath.h>

#include "GraphicsEngine.h"
#include "VertexMesh.h"

Mesh::Mesh(const wchar_t* full_path) : Resource(full_path)
{
    std::string file_path = std::filesystem::path(full_path).string();
    tinyobj::attrib_t attributes;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> material;
    std::string warning, error;

    bool res = tinyobj::LoadObj(&attributes, &shapes, &material, &warning, &error, file_path.c_str());

    if (!error.empty()) throw std::exception("Mesh not created successfully");
    if (!res) throw std::exception("Mesh not created successfully");
    if (shapes.size() > 1) throw std::exception("Mesh not created successfully");

    std::vector<VertexMesh> list_vertices;
    std::vector<unsigned int> list_indices;

    for (size_t s = 0; s < shapes.size(); s++)
    {
        size_t index_offset = 0;
        list_vertices.reserve(shapes[s].mesh.indices.size());
        list_indices.reserve(shapes[s].mesh.indices.size());

        for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++)
        {
            unsigned char num_face_verts = shapes[s].mesh.num_face_vertices[f];

            for (unsigned char v = 0; v < num_face_verts; v++)
            {
                tinyobj::index_t index = shapes[s].mesh.indices[index_offset + v];

                tinyobj::real_t vx = attributes.vertices[index.vertex_index * 3 + 0];
                tinyobj::real_t vy = attributes.vertices[index.vertex_index * 3 + 1];
                tinyobj::real_t vz = attributes.vertices[index.vertex_index * 3 + 2];

                tinyobj::real_t tx = attributes.texcoords[index.texcoord_index * 2 + 0];
                tinyobj::real_t ty = attributes.texcoords[index.texcoord_index * 2 + 1];

                VertexMesh vertex(DirectX::XMFLOAT3(vx, vy, vz), DirectX::XMFLOAT2(tx, ty));
                list_vertices.push_back(vertex);

                list_indices.push_back((unsigned int)index_offset + v);
            }

            index_offset += num_face_verts;
        }
    }

    void* shader_byte_code = nullptr;
    size_t size_shader = 0;
    GraphicsEngine::getInstance()->getVertexMeshLayoutShaderByteCodeAndSize(&shader_byte_code, &size_shader);
    m_vertex_buffer = GraphicsEngine::getInstance()->getRenderSystem()->createVertexBuffer(&list_vertices[0], sizeof(VertexMesh),
        (UINT)list_vertices.size(), shader_byte_code, (UINT)size_shader);
    m_index_buffer = GraphicsEngine::getInstance()->getRenderSystem()->createIndexBuffer(&list_indices[0], (UINT)list_indices.size());

}

Mesh::~Mesh()
{
}

const VertexBufferPtr& Mesh::getVertexBuffer()
{
    return m_vertex_buffer;
}

const IndexBufferPtr& Mesh::getIndexBuffer()
{
    return m_index_buffer;
}
