struct PS_INPUT
{
    float4 position : SV_POSITION;
    float3 color : COLOR;
};

cbuffer constant : register(b0)
{
    float3 light_position;
    float light_intensity;

    float3 light_direction;
    float spec_phong;

    float3 light_color;
    float spec_strength;

    float3 light_ambient_color;
    float light_ambient_strength;
	
    float range;
    float outer_angle;
    float inner_angle;
    float attenuation;
}

float4 psmain(PS_INPUT input) : SV_TARGET
{
    float3 fragPos = input.position.xyz;
    float3 toLight = normalize(light_position - fragPos);
    float cosTheta = dot(-light_direction, toLight);

    return float4(cosTheta, cosTheta, cosTheta, 1.0);
}

float4 unlit(PS_INPUT input) : SV_TARGET
{
    return float4(input.color, 1.0f);
}