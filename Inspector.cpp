#include "Inspector.h"
#include "GameObjectManager.h"

Inspector::Inspector() : AUIScreen("Inspector")
{
}

Inspector::~Inspector()
{
}

void Inspector::drawUI()
{
    ImGui::Begin("Inspector");

    AGameObject* object = GameObjectManager::getInstance()->getSelectedObject();

    if (object != nullptr)
    {
        XMVECTOR v_position = object->getLocalPosition();
        XMVECTOR v_rotation = object->getLocalRotation();
        XMVECTOR v_scale = object->getLocalScale();

        float position[3] =
        {
            XMVectorGetX(v_position),
            XMVectorGetY(v_position),
            XMVectorGetZ(v_position)
        };

        float rotation[3] =
        {
            XMVectorGetX(v_rotation),
            XMVectorGetY(v_rotation),
            XMVectorGetZ(v_rotation)
        };

        float scale[3] =
        {
            XMVectorGetX(v_scale),
            XMVectorGetY(v_scale),
            XMVectorGetZ(v_scale)
        };

        ImGui::Text("Object: %s", object->getName().c_str());

        if (ImGui::TreeNode("Transform"))
        {
            if (ImGui::DragFloat3("Position", position, 0.1f, -180.0f, 180.0f))
            {
                object->setPosition(XMVectorSet(position[0], position[1], position[2], 0.0f));
            }
            if (ImGui::DragFloat3("Rotation", rotation, 0.1f))
            {
                object->setRotation(XMVectorSet(rotation[0], rotation[1], rotation[2], 0.0f));
            }
            if (ImGui::DragFloat3("Scale", scale, 0.1f))
            {
                object->setScale(XMVectorSet(scale[0], scale[1], scale[2], 0.0f));
            }
            ImGui::TreePop();
        }
    }

    else
    {
        ImGui::Text("No object selected.");
    }

    ImGui::End();
}
