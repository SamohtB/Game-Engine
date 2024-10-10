struct PS_INPUT
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
    float elapsedTime;
};

float4 psmain(PS_INPUT input) : SV_TARGET
{
    float lerpFactor = (sin(elapsedTime) + 1.0f) * 0.5f;
    
    return float4(lerp(input.color, input.color1, lerpFactor), 1.0f);
}