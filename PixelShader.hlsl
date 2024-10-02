struct PS_INPUT
{
    float4 position : SV_POSITION;
    float3 color : COLOR;
};

cbuffer constant : register(b0)
{
    float4 directionalLightDir;
    float4 directionalLightColor;
    float4 directionalLightAmbientColor;
    float4 lightingParams; // x = ambientStr, y = specPhong, z = specStr, w = dirLightIntensity
    float4 cameraPos;
}

float3 CalculateDirectionalLight(float3 normal)
{
    normal = normalize(normal);
    float3 lightDir = normalize(directionalLightDir.xyz);
    
    float diff = max(dot(normal, lightDir), 0.0);
    float3 diffuse = diff * directionalLightColor.xyz;

    float3 ambientCol = directionalLightAmbientColor.xyz * lightingParams.x;

    float3 viewDir = normalize(cameraPos.xyz);
    float3 reflectDir = reflect(-lightDir, normal);

    float spec = pow(max(dot(reflectDir, viewDir), 0.0), lightingParams.y);
    float3 specColor = spec * lightingParams.z * directionalLightColor.xyz;

    float3 finalColor = (specColor + diffuse + ambientCol) * lightingParams.w;

    return finalColor;
}

float4 psmain(PS_INPUT input) : SV_TARGET
{
    float3 normal = float3(0.0, 0.0, 1.0);
    float3 directionalLight = CalculateDirectionalLight(normal);
    float3 litColor = directionalLight * input.color;
    
    return float4(litColor, 1.0f);
}