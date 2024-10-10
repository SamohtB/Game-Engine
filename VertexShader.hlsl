struct VS_INPUT
{
    float3 position : POSITION;
    float3 color : COLOR;
    float3 color1 : COLOR1;
};

struct VS_OUTPUT
{
    float4 position : SV_POSITION;
    float3 color : COLOR;
    float3 color1 : COLOR1;
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
 
    float4 pos = float4(input.position, 1.0f);
    float4 worldPosition = mul(pos, m_world);
    float4 viewPosition = mul(worldPosition, m_view);
    output.position = mul(viewPosition, m_projection);
    
    output.color = input.color;
    output.color1 = input.color1;
    return output;
}