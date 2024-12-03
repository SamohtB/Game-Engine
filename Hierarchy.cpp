#include "Hierarchy.h"

Hierarchy::Hierarchy() : AUIScreen("Hierarchy")
{
}

Hierarchy::~Hierarchy()
{
}

void Hierarchy::drawUI()
{
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.2f, 0.2f, 0.2f, 0.9f));

    ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;

    if (ImGui::Begin("Hierarchy", nullptr, window_flags))
    {

        GameObjectManager::List object_list = GameObjectManager::getInstance()->getAllObjects();

        for (AGameObject* game_object : object_list)
        {
            drawGameObjectNode(game_object);
        }
    }

    ImGui::End();

    ImGui::PopStyleColor();
}

void Hierarchy::drawGameObjectNode(AGameObject* game_object)
{
    bool is_selected = (GameObjectManager::getInstance()->getSelectedObject() == game_object);
    
    if (is_selected)
    {
        ImGui::PushStyleColor(ImGuiCol_Header, ImVec4(0.3f, 0.6f, 0.3f, 1.0f)); // Green for selected
        ImGui::PushStyleColor(ImGuiCol_HeaderHovered, ImVec4(0.5f, 0.8f, 0.5f, 1.0f)); // Hover effect
    }
    else
    {
        ImGui::PushStyleColor(ImGuiCol_Header, ImVec4(0.2f, 0.2f, 0.2f, 1.0f)); // Default color
        ImGui::PushStyleColor(ImGuiCol_HeaderHovered, ImVec4(0.4f, 0.4f, 0.4f, 1.0f)); // Hover effect
    }

    if (ImGui::Selectable(game_object->getName().c_str(), is_selected))
    {
        if (is_selected)
        {
            GameObjectManager::getInstance()->setSelectedObject(nullptr);
        }
        else
        {
            GameObjectManager::getInstance()->setSelectedObject(game_object);
        }
    }

    if (is_selected)
    {
        ImVec2 cursorPos = ImGui::GetCursorPos();
        ImGui::SameLine(ImGui::GetContentRegionAvail().x - ImGui::CalcTextSize("Delete").x - ImGui::GetStyle().ItemSpacing.x * 2);
        ImGui::SetCursorPosY(cursorPos.y + ImGui::GetStyle().ItemSpacing.y / 2);

        if (ImGui::Button("Delete"))
        {
            GameObjectManager::getInstance()->deleteObject(game_object);
            GameObjectManager::getInstance()->setSelectedObject(nullptr);
        }
    }

    ImGui::PopStyleColor(2);
}
