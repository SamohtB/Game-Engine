struct PS_INPUT
{
    float4 position : SV_POSITION;
    float3 color : COLOR;
    float2 texcoord : TEXCOORD;
};

cbuffer constant : register(b0)
{
    row_major float4x4 m_world;
    row_major float4x4 m_view;
    row_major float4x4 m_projection;
};

float4 psmain(PS_INPUT input) : SV_TARGET
{
    return float4(input.color, 1.0f);
}