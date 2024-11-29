#include "AComponent.h"

AComponent::AComponent(String name, ComponentType type, AGameObject* owner) : m_name(name), m_component_type(type), m_owner(owner)
{
}

AComponent::~AComponent()
{
}

void AComponent::attachOwner(AGameObject* owner)
{
    this->m_owner = owner;
}

void AComponent::detachOwner()
{
    this->m_owner = nullptr;
}

AGameObject* AComponent::getOwner()
{
    return this->m_owner;
}

AComponent::ComponentType AComponent::getType()
{
    return this->m_component_type;
}

String AComponent::getName()
{
    return this->m_name;
}
