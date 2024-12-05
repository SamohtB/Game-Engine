#include "AGameObject.h"
#include "EditorAction.h"
#include "PhysicsComponent.h"

typedef std::string String;
typedef std::vector<AComponent*> ComponentList;

AGameObject::AGameObject(String name) : m_name(name)
{
	this->m_local_position = XMFLOAT3(0, 0, 0);
	this->m_local_rotation = XMFLOAT3(0, 0, 0);
	this->m_local_scale = XMFLOAT3(1, 1, 1);
    this->m_local_matrix = XMMatrixIdentity();
}

AGameObject::~AGameObject()
{
    for (int i = 0; i < this->m_component_list.size(); i++) {
        this->m_component_list[i]->detachOwner();
    }
    this->m_component_list.clear();
}

bool AGameObject::isActive()
{
    return this->active;
}

void AGameObject::setActive(bool value)
{
    this->active = value;
}

void AGameObject::setPosition(float x, float y, float z)
{
	m_local_position = XMFLOAT3(x, y, z);
}

void AGameObject::setPosition(XMVECTOR vector)
{
	XMStoreFloat3(&this->m_local_position, vector);
}

XMVECTOR AGameObject::getLocalPosition()
{
	return XMLoadFloat3(&this->m_local_position);
}

void AGameObject::setRotation(float pitch, float yaw, float roll)
{
	m_local_rotation = XMFLOAT3(pitch, yaw, roll);
}

void AGameObject::setRotation(XMVECTOR vector)
{
	XMStoreFloat3(&this->m_local_rotation, vector);
}

void AGameObject::rotate(float pitch, float yaw, float roll)
{
	XMVECTOR currentRotation = XMLoadFloat3(&this->m_local_rotation);
	XMVECTOR newRotation = XMVectorSet(pitch, yaw, roll, 0.0f);
	XMVECTOR combinedRotation = XMVectorAdd(currentRotation, newRotation);
	XMStoreFloat3(&this->m_local_rotation, combinedRotation);
}

XMVECTOR AGameObject::getLocalRotation()
{
	return XMLoadFloat3(&this->m_local_rotation);
}

void AGameObject::setScale(float x, float y, float z)
{
	m_local_scale = XMFLOAT3(x, y, z);
}

void AGameObject::setScale(XMVECTOR vector)
{
	XMStoreFloat3(&this->m_local_scale, vector);
}

void AGameObject::scale(float scale)
{
	XMVECTOR currentScale = XMLoadFloat3(&this->m_local_scale);
	XMVECTOR newScale = XMVectorSet(scale, scale, scale, 0.0f);
	XMVECTOR combinedRotation = XMVectorAdd(currentScale, newScale);
	XMStoreFloat3(&this->m_local_scale, combinedRotation);
}

XMVECTOR AGameObject::getLocalScale()
{
	return XMLoadFloat3(&this->m_local_scale);
}

AGameObject::String AGameObject::getName()
{
    return this->m_name;
}

void AGameObject::setName(String name)
{
    this->m_name = name;
}

void AGameObject::setObjectType(PrimitiveType type)
{
    this->m_type = type;
}

AGameObject::PrimitiveType AGameObject::getObjectType()
{
    return this->m_type;
}

void AGameObject::attachComponent(AComponent* component)
{
    this->m_component_list.push_back(component);
    component->attachOwner(this);
}

void AGameObject::detachComponent(AComponent* component)
{
    int index = -1;
    for (int i = 0; i < this->m_component_list.size(); i++) {
        if (this->m_component_list[i] == component) {
            index = i;
            break;
        }
    }

    if (index != -1) {
        this->m_component_list.erase(this->m_component_list.begin() + index);
    }
}

AComponent* AGameObject::findComponentByName(String name)
{
    for (int i = 0; i < this->m_component_list.size(); i++)
    {
        if (this->m_component_list[i]->getName() == name)
        {
            return this->m_component_list[i];
        }
    }

    return nullptr;
}

AComponent* AGameObject::findComponentOfType(AComponent::ComponentType type, String name)
{
    for (int i = 0; i < this->m_component_list.size(); i++)
    {
        if (this->m_component_list[i]->getName() == name && this->m_component_list[i]->getType() == type)
        {
            return this->m_component_list[i];
        }
    }

    return nullptr;
}

ComponentList AGameObject::getComponentsOfType(AComponent::ComponentType type)
{
    ComponentList foundList;
    for (int i = 0; i < this->m_component_list.size(); i++)
    {
        if (this->m_component_list[i]->getType() == type)
        {
            foundList.push_back(this->m_component_list[i]);
        }
    }

    return foundList;
}

ComponentList AGameObject::getComponentsOfTypeRecursive(AComponent::ComponentType type)
{
    ComponentList foundList;
    for (int i = 0; i < this->m_component_list.size(); i++)
    {
        if (this->m_component_list[i]->getType() == type)
        {
            foundList.push_back(this->m_component_list[i]);
        }
    }

    return foundList;
}

void AGameObject::updateLocalMatrix()
{
    XMMATRIX scaleMatrix = XMMatrixScalingFromVector(XMLoadFloat3(&this->m_local_scale));
    XMMATRIX rotationMatrix = XMMatrixRotationRollPitchYawFromVector(XMLoadFloat3(&this->m_local_rotation));
    XMMATRIX translationMatrix = XMMatrixTranslationFromVector(XMLoadFloat3(&this->m_local_position));

    this->m_local_matrix = scaleMatrix * rotationMatrix * translationMatrix;
}

float* AGameObject::getMatrix()
{
    static XMFLOAT4X4 matrixResult;
    XMStoreFloat4x4(&matrixResult, this->m_local_matrix);

    return reinterpret_cast<float*>(&matrixResult);
}

float* AGameObject::getPhysicsLocalMatrix()
{
    XMMATRIX allMatrix = XMMatrixIdentity();

    /* position matrix */
    XMVECTOR localPosition = this->getLocalPosition();
    XMMATRIX translationMatrix = XMMatrixTranslationFromVector(localPosition);

    /* scale matrix */
    XMMATRIX scaleMatrix = XMMatrixScaling(1.0f, 1.0f, 1.0f);

    /* rotation matrix */
    XMVECTOR rotation = this->getLocalRotation();
    float pitch = XMVectorGetX(rotation);
    float yaw = XMVectorGetY(rotation);
    float roll = XMVectorGetZ(rotation);

    XMMATRIX xMatrix = XMMatrixRotationX(pitch);
    XMMATRIX yMatrix = XMMatrixRotationY(yaw);
    XMMATRIX zMatrix = XMMatrixRotationZ(roll);

    XMMATRIX rotMatrix = XMMatrixMultiply(xMatrix, XMMatrixMultiply(yMatrix, zMatrix));
    allMatrix = XMMatrixMultiply(scaleMatrix, XMMatrixMultiply(rotMatrix, translationMatrix));

    static XMFLOAT4X4 matrixResult;
    XMStoreFloat4x4(&matrixResult, allMatrix);

    return reinterpret_cast<float*>(&matrixResult);
}

XMMATRIX AGameObject::getLocalMatrix()
{
    return this->m_local_matrix;  
}

void AGameObject::setLocalMatrix(float* matrix)
{
    XMMATRIX newMatrix = XMMatrixSet(
        matrix[0], matrix[1], matrix[2], matrix[3],
        matrix[4], matrix[5], matrix[6], matrix[7],
        matrix[8], matrix[9], matrix[10], matrix[11],
        matrix[12], matrix[13], matrix[14], matrix[15]
    );

    XMMATRIX scaleMatrix = XMMatrixScalingFromVector(XMLoadFloat3(&this->m_local_scale));
    XMMATRIX rotationMatrix = XMMatrixRotationRollPitchYawFromVector(XMLoadFloat3(&this->m_local_rotation));
    XMMATRIX translationMatrix = XMMatrixTranslationFromVector(XMLoadFloat3(&this->m_local_position));

    this->m_local_matrix = scaleMatrix * rotationMatrix * newMatrix * translationMatrix;
}

void AGameObject::setLocalMatrix(XMMATRIX matrix)
{
    this->m_local_matrix = matrix;
}

void AGameObject::saveEditState()
{
    if (this->m_last_edit_state == NULL)
    {
        this->m_last_edit_state = new EditorAction(this);
    }
}

void AGameObject::restoreEditState()
{
    if (this->m_last_edit_state != NULL)
    {
        XMStoreFloat3(&this->m_local_position, this->m_last_edit_state->getStorePos());
        XMStoreFloat3(&this->m_local_scale, this->m_last_edit_state->getStoredScale());
        XMStoreFloat3(&this->m_local_rotation, this->m_last_edit_state->getStoredOrientation());
        this->m_local_matrix = this->m_last_edit_state->getStoredMatrix();

        /* reset rigidbody */
        PhysicsComponent* physics = static_cast<PhysicsComponent*>(this->getComponentsOfType(AComponent::Physics)[0]);

        if (physics != nullptr)
        {
            rp3d::Transform transform = physics->getRigidBody()->getTransform();

            // Reset the position
            rp3d::Vector3 newPosition(this->m_local_position.x, this->m_local_position.y, this->m_local_position.z);
            transform.setPosition(newPosition);

            // Reset the orientation
            rp3d::Quaternion newOrientation = eulerToQuaternion(this->m_local_rotation.x, this->m_local_rotation.y, this->m_local_rotation.z);
            transform.setOrientation(newOrientation);

            // Apply the updated transform back to the rigidbody
            physics->getRigidBody()->setTransform(transform);
        }

        this->m_last_edit_state = NULL;
    }
    else
    {
        std::cout << "Edit state is null. Cannot restore." << std::endl;
    }
}

void AGameObject::awake()
{

}

inline rp3d::Quaternion eulerToQuaternion(float pitch, float yaw, float roll)
{
    // Convert to radians
    float pitchRad = XMConvertToRadians(pitch);
    float yawRad = XMConvertToRadians(yaw);
    float rollRad = XMConvertToRadians(roll);

    float cy = cosf(yawRad * 0.5f);
    float sy = sinf(yawRad * 0.5f);
    float cp = cosf(pitchRad * 0.5f);
    float sp = sinf(pitchRad * 0.5f);
    float cr = cosf(rollRad * 0.5f);
    float sr = sinf(rollRad * 0.5f);

    rp3d::Quaternion q;
    q.w = cr * cp * cy + sr * sp * sy;
    q.x = sr * cp * cy - cr * sp * sy;
    q.y = cr * sp * cy + sr * cp * sy;
    q.z = cr * cp * sy - sr * sp * cy;

    return q;
}
