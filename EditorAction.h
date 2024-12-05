#pragma once
#include <iostream>
#include "AGameObject.h"

class EditorAction
{
public:
    EditorAction(AGameObject* gameObject);
    ~EditorAction();

    AGameObject::String getOwnerName();
    XMVECTOR getStorePos();
    XMVECTOR getStoredScale();
    XMVECTOR getStoredOrientation();
    XMMATRIX getStoredMatrix();

private:
    AGameObject::String m_object_name;
    XMVECTOR m_local_position;
    XMVECTOR m_local_scale;
    XMVECTOR m_orientation;
    XMMATRIX m_local_matrix;
};
