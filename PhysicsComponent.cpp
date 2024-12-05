#include "PhysicsComponent.h"
#include "BaseComponentSystem.h"
#include "PhysicsSystem.h"
#include "DirectXMath.h"
#include "AGameObject.h"

using namespace DirectX;

PhysicsComponent::PhysicsComponent(String name, AGameObject* owner) : AComponent(name, ComponentType::Physics, owner)
{
    /* register */
    BaseComponentSystem::getInstance()->getPhysicsSystem()->registerComponent(this);
    PhysicsCommon* physics_common = BaseComponentSystem::getInstance()->getPhysicsSystem()->getPhysicsCommon();
    PhysicsWorld* physics_world = BaseComponentSystem::getInstance()->getPhysicsSystem()->getPhysicsWorld();

    /* add rigidbody */
    XMVECTOR scale = this->m_owner->getLocalScale();
    Transform transform;
    transform.setFromOpenGL(this->getOwner()->getPhysicsLocalMatrix());

    BoxShape* boxShape = physics_common->createBoxShape(Vector3(XMVectorGetX(scale) / 2, XMVectorGetY(scale) / 2, XMVectorGetZ(scale) / 2));
    this->m_rigidbody = physics_world->createRigidBody(transform);
    this->m_rigidbody->addCollider(boxShape, transform);
    this->m_rigidbody->updateMassPropertiesFromColliders();
    this->m_rigidbody->setMass(this->m_mass);
    this->m_rigidbody->setType(BodyType::DYNAMIC);

    transform = this->m_rigidbody->getTransform();
    float matrix[16];
    transform.getOpenGLMatrix(matrix);

    this->getOwner()->setLocalMatrix(matrix);
}

PhysicsComponent::~PhysicsComponent()
{
    BaseComponentSystem::getInstance()->getPhysicsSystem()->unregisterComponent(this);

    if (this->m_rigidbody)
    {
        PhysicsWorld* physicsWorld = BaseComponentSystem::getInstance()->getPhysicsSystem()->getPhysicsWorld();
        if (physicsWorld)
        {
            physicsWorld->destroyRigidBody(this->m_rigidbody);
        }
        this->m_rigidbody = nullptr;
    }
}

void PhysicsComponent::perform(float deltaTime)
{
    const Transform transform = this->m_rigidbody->getTransform();
    float matrix[16];
    transform.getOpenGLMatrix(matrix);

    this->getOwner()->setLocalMatrix(matrix);

    rp3d::Vector3 position = transform.getPosition();
    this->getOwner()->setPosition(position.x , position.y, position.z);

    rp3d::Quaternion orientation = transform.getOrientation();
    XMVECTOR quat = XMVectorSet(orientation.x, orientation.y, orientation.z, orientation.w);

    XMFLOAT3 euler;
    XMStoreFloat3(&euler, XMQuaternionRotationRollPitchYawFromVector(quat));

    this->getOwner()->setRotation(euler.x, euler.y, euler.z);
}

RigidBody* PhysicsComponent::getRigidBody()
{
    return this->m_rigidbody;
}

void PhysicsComponent::setBodyType(BodyType type)
{
    this->m_rigidbody->setType(type);
}
