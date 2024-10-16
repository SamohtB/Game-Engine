struct VS_INPUT
{
    float4 position : POSITION;
    float3 color : COLOR;
};

struct VS_OUTPUT
{
    float4 position : SV_POSITION;
    float3 color : COLOR;
};

cbuffer constant : register(b0)
{
    row_major float4x4 m_world;
    row_major float4x4 m_view;
    row_major float4x4 m_projection;
    float deltaTime;
};

VS_OUTPUT vsmain(VS_INPUT input)
{
    VS_OUTPUT output = (VS_OUTPUT) 0;
    
    float4 worldPosition = mul(input.position, m_world);
    float4 viewPosition = mul(worldPosition, m_view);
    output.position = mul(viewPosition, m_projection);
    
    output.color = input.color;
    return output;
}