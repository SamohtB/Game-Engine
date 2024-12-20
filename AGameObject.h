#pragma once
#include "AComponent.h"
#include "GraphicsEngine.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "PhysicsComponent.h"
#include <string>
#include <vector>
#include <DirectXMath.h>

using namespace DirectX;

class GameObjectManager;
class VertexShader;
class PixelShader;
class EditorAction;

class AGameObject
{

public:

    typedef std::string String;
    typedef std::vector<AComponent*> ComponentList;

    enum PrimitiveType {
        NOTSET = -1,
        CAMERA = 0,
        CUBE,
        PLANE,
        SPHERE,
        CYLINDER,
        CAPSULE,
        MESH
    };

    struct vertex
    {
        XMFLOAT3 position;
        XMFLOAT2 texcoord;
        XMFLOAT3 color;
    };

    struct alignas(16) constant
    {
        XMMATRIX m_world;
        XMMATRIX m_view;
        XMMATRIX m_projection_matrix;
    };

	AGameObject(String name);
	virtual ~AGameObject();
	
	virtual void update(float deltaTime) = 0;
	virtual void draw(int width, int height) = 0;

	bool isActive();
	void setActive(bool value);

	void setPosition(float x, float y, float z);
	void setPosition(XMVECTOR vector);
	XMVECTOR getLocalPosition();

	void setRotation(float pitch, float yaw, float roll);
	void setRotation(XMVECTOR vector);
	void rotate(float pitch, float yaw, float roll);
	XMVECTOR getLocalRotation();

	void setScale(float x, float y, float z);
	void setScale(XMVECTOR vector);
	void scale(float scale);
	XMVECTOR getLocalScale();

    String getName();
    void setName(String name);
    void setObjectType(PrimitiveType type);
    PrimitiveType getObjectType();
    TextureManager::TextureType getTextureType();
    void setTextureType(TextureManager::TextureType type);
    
    void attachComponent(AComponent* component);
    void detachComponent(AComponent* component);

    AComponent* findComponentByName(String name);
    AComponent* findComponentOfType(AComponent::ComponentType type, String name);
    ComponentList getComponentsOfType(AComponent::ComponentType type);
    ComponentList getComponentsOfTypeRecursive(AComponent::ComponentType type);

    void updateLocalMatrix(); 
    float* getMatrix();
    
    float* getPhysicsLocalMatrix();
    XMMATRIX getLocalMatrix();
    void setLocalMatrix(float* matrix);
    void setLocalMatrix(XMMATRIX matrix);

    virtual void saveEditState();
    virtual void restoreEditState();

    rp3d::Quaternion eulerToQuaternion(float pitch, float yaw, float roll);

protected:
    String m_name;
	XMFLOAT3 m_local_position;
    XMFLOAT3 m_local_rotation;
	XMFLOAT3 m_local_scale;
	XMMATRIX m_local_matrix;

    PrimitiveType m_primitive_type = NOTSET;
    TextureManager::TextureType m_texture_type = TextureManager::NONE;

    ComponentList m_component_list;

    virtual void awake();
	
private:
    bool active = true;
    EditorAction* m_last_edit_state = nullptr;

    friend class GameObjectManager;
};
