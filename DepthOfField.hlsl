struct PS_INPUT
{
    float4 position : SV_POSITION;
    float3 color : COLOR;
};

cbuffer constant : register(b0)
{
    matrix m_world;
    matrix m_view;
    matrix m_projection_matrix;
    float focalPlane;
    float focusRange;
    float blurRange;
    float buffer;
};

float4 main(PS_INPUT input) : SV_TARGET
{
    float kernel[5] = { 0.2270270270, 0.1945945946, 0.1216216216, 0.0540540541, 0.0162162162 };

    float2 texelSize = float2(1.0 / screenWidth, 1.0 / screenHeight);
    float4 color = float4(0, 0, 0, 0);

    for (int i = -2; i <= 2; ++i)
    {
        for (int j = -2; j <= 2; ++j)
        {
            float2 offset = float2(i, j) * texelSize * blurRange;
            float3 sampleColor = shaderTexture.Sample(SampleType, input.tex + offset).rgb;
            color.rgb += sampleColor * kernel[abs(i)] * kernel[abs(j)];
        }
    }

    return float4(color.rgb, 1.0f);
}
