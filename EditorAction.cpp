#include "EditorAction.h"

EditorAction::EditorAction(AGameObject* gameObject)
{
    this->m_object_name = gameObject->getName();
    this->m_local_position = gameObject->getLocalPosition();
    this->m_orientation = gameObject->getLocalRotation();
    this->m_local_scale = gameObject->getLocalScale();
    this->m_local_matrix = gameObject->getLocalMatrix();
}

EditorAction::~EditorAction()
{
}

AGameObject::String EditorAction::getOwnerName()
{
    return this->m_object_name;
}

XMVECTOR EditorAction::getStorePos()
{
    return this->m_local_position;
}

XMVECTOR EditorAction::getStoredScale()
{
    return this->m_local_scale;
}

XMVECTOR EditorAction::getStoredOrientation()
{
    return this->m_orientation;
}

XMMATRIX EditorAction::getStoredMatrix()
{
    return this->m_local_matrix;
}
