struct PS_INPUT
{
    float4 position : SV_POSITION;
    float3 color : COLOR;
    float3 color1 : COLOR1;
};

cbuffer constant : register(b0)
{
    float deltaTime;
};

float Repeat(float value, float length)
{
    return value - length * floor(value / length);
}

float4 psmain(PS_INPUT input) : SV_TARGET
{
    float speedFactor = ((cos(deltaTime * 0.5f) + 1.0f) / 2.0f);
    float lerpFactor = (sin(deltaTime + (deltaTime * speedFactor)) + 1.0f) * 0.5f;
    //float lerpFactor = (sin(deltaTime) + 1.0f) * 0.5f;
    
    return float4(lerp(input.color, input.color1, lerpFactor), 1.0f);
}