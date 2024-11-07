struct VS_INPUT
{
    float4 position : POSITION;
    float3 color : COLOR;
};

struct PS_INPUT
{
    float4 position : SV_POSITION;
    float3 color : COLOR;
};

cbuffer constant : register(b0)
{
    matrix m_world;
    matrix m_view;
    matrix m_projection;
    float offset;
};

PS_INPUT main(VS_INPUT input)
{
    PS_INPUT output;

    float4 worldPosition = mul(input.position, m_world);
    float4 viewPosition = mul(worldPosition, m_view);
    output.position = mul(viewPosition, m_projection);

    output.position.xy += offset;
    output.color = input.color;

    return output;
}
