#pragma once
#include "GameObject.h"

class Object3D : public GameObject
{
public:
	Object3D() {}
	~Object3D() {}

	void release() override;
	void draw() override;
	void loadShaders(const wchar_t* vsPath, const char* vsEntry, const wchar_t* psPath, const char* psEntry) override;

protected:
	std::vector<unsigned int> index_list;

private:
	IndexBuffer* indexBuffer = nullptr;
};

