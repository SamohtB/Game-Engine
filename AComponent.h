#pragma once
#include <string>

class AGameObject;

typedef std::string String;


class AComponent
{
public:
    enum ComponentType { NotSet = -1, Script = 0, Renderer, Input, Physics };

    AComponent(String name, ComponentType type, AGameObject* owner);
    ~AComponent();

    void attachOwner(AGameObject* owner);
    void detachOwner();
    AGameObject* getOwner();
    ComponentType getType();
    String getName();

    virtual void perform(float deltaTime) = 0;

protected:
    AGameObject* m_owner;
    ComponentType m_component_type;
    String m_name;
};

