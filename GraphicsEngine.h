#pragma once
#include <d3d11.h>

class GraphicsEngine
{
public:
	GraphicsEngine();
	~GraphicsEngine();
	bool init();
	bool release();

public:
	static GraphicsEngine* get();

private:
	ID3D11Device* m_ded_device;
	D3D_FEATURE_LEVEL m_feature_levels;
	ID3D11DeviceContext* m_imm_context;
};

