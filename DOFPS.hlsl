Texture2D sceneTexture : register(t0); // Scene texture
Texture2D depthTexture : register(t1); // Depth texture
SamplerState samplerState : register(s0);

float4 main(float2 texcoord : TEXCOORD) : SV_Target
{
    float depth = depthTexture.Sample(samplerState, texcoord).r; // Get depth from depth texture
    float blurAmount = smoothstep(0.2, 0.8, depth); // Adjust blur based on depth value
    
    // Sample from the scene texture and apply blur effect based on depth
    float4 color = sceneTexture.Sample(samplerState, texcoord);
    color.rgb *= blurAmount; // Adjust the color based on depth
    
    return color;
}
