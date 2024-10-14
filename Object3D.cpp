#include "Object3D.h"

void Object3D::draw()
{
	GameObject::draw();

	DeviceContext* context = GraphicsEngine::getInstance()->getImmediateDeviceContext();
	
	context->setIndexBuffer(this->indexBuffer);

	context->drawIndexed(this->indexBuffer->getSizeIndexList(), 0, 0, m_topology);
}

void Object3D::loadShaders(const wchar_t* vsPath, const char* vsEntry, const wchar_t* psPath, const char* psEntry)
{
	indexBuffer = GraphicsEngine::getInstance()->createIndexBuffer();
	UINT size_index_list = static_cast<UINT>(index_list.size());
	indexBuffer->load(this->index_list.data(), size_index_list * sizeof(unsigned int));

	GameObject::loadShaders(vsPath, vsEntry, psPath, psEntry);
}

void Object3D::release()
{
	GameObject::release();

	if (indexBuffer)
	{
		indexBuffer->release();
		indexBuffer = nullptr;
	}

}