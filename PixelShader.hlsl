Texture2D Texture : register(t0);
sampler TextureSampler : register(s0);

struct PS_INPUT
{
    float4 position : POSITION;
    float2 texcoord : TEXCOORD0;
};

cbuffer constant : register(b0)
{
    row_major float4x4 m_world;
    row_major float4x4 m_view;
    row_major float4x4 m_projection;
};

float4 psmain(PS_INPUT input) : SV_TARGET
{
    return float4(1.0f, 0.0f, 0.0f, 1.f);
}
