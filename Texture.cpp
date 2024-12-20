#include "Texture.h"
#include "GraphicsEngine.h"
#include "RenderSystem.h"
#include <DirectXTex.h>

Texture::Texture(const wchar_t* full_path) : Resource(full_path)
{
    DirectX::ScratchImage image_data;
    HRESULT res = DirectX::LoadFromWICFile(full_path, DirectX::WIC_FLAGS_NONE, nullptr, image_data);

    if (SUCCEEDED(res))
    {
        res = DirectX::CreateTexture(GraphicsEngine::getInstance()->getRenderSystem()->getDirectXDevice(),
            image_data.GetImages(), image_data.GetImageCount(), image_data.GetMetadata(), &m_texture);

        D3D11_SHADER_RESOURCE_VIEW_DESC desc = {};
        desc.Format = image_data.GetMetadata().format;
        desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
        desc.Texture2D.MipLevels = static_cast<UINT>(image_data.GetMetadata().mipLevels);
        desc.Texture2D.MostDetailedMip = 0;

        GraphicsEngine::getInstance()->getRenderSystem()->getDirectXDevice()->CreateShaderResourceView(m_texture, &desc, &m_shader_resource_view);
    }
    else
    {
        throw std::exception("Texture not created successfully");
    }
}

Texture::~Texture()
{
    if (m_texture) m_texture->Release();
}
