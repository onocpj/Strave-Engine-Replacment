#include <StraveEngine/Entity/GameObject.hpp>
#include <StraveEngine/System/ExceptionHandler.hpp>
#include <StraveEngine/Entity/GameObjectContainer.hpp>


namespace Strave
{
	void DeleteComponent(IComponent* component);

	////////////////////////////////////////////////////////////
	// GameObject
	////////////////////////////////////////////////////////////
	GameObject::GameObject() :
		Object(),
		m_KEY(GO_KEY_UNASSIGNED),
		m_Transform(new Transform(this)),
		m_Mesh(new Mesh(this)),
		m_Camera(UNDEF_PTR),
		m_RigidBody(UNDEF_PTR),
		m_Collider(UNDEF_PTR),
		m_ParticleSystem(UNDEF_PTR),
		m_Animation(UNDEF_PTR),
		m_Audio(UNDEF_PTR),
		m_CharacterController(UNDEF_PTR),
		m_AIController(UNDEF_PTR)
	{
		m_Transform->ApplyTransforms();
		ExceptionHandler::Handle(GameObjectContainer::Insert(*this, this->m_KEY));
	}

	GameObject::GameObject(std::string name) :
		Object(name),
		m_KEY(GO_KEY_UNASSIGNED),
		m_Transform(new Transform(this)),
		m_Mesh(new Mesh(this)),
		m_Camera(UNDEF_PTR),
		m_RigidBody(UNDEF_PTR),
		m_Collider(UNDEF_PTR),
		m_ParticleSystem(UNDEF_PTR),
		m_Animation(UNDEF_PTR),
		m_Audio(UNDEF_PTR),
		m_CharacterController(UNDEF_PTR),
		m_AIController(UNDEF_PTR)
	{
		m_Transform->ApplyTransforms();
		ExceptionHandler::Handle(GameObjectContainer::Insert(*this, this->m_KEY));
	}

	GameObject::~GameObject()
	{
		// Maybe should not delete those components because IComponent class is 
		// derived from ICollctable and memory deletion is handled by engine !!
		// It should not cause any problems, because nullptr memory is treated 
		// by garbage collector

		DeleteComponent(m_Transform);
		DeleteComponent(m_Mesh);
		DeleteComponent(m_Camera);
		DeleteComponent(m_RigidBody);
		DeleteComponent(m_Collider);
		DeleteComponent(m_ParticleSystem);
		DeleteComponent(m_Animation);
		DeleteComponent(m_Audio);
		DeleteComponent(m_CharacterController);
		DeleteComponent(m_AIController);
	}

	GameObject::GameObject(const GameObject& object) :
		Object(object)
	{
		m_Transform = object.m_Transform;
		m_Mesh = object.m_Mesh;
		m_Camera = object.m_Camera;
		m_RigidBody = object.m_RigidBody;
		m_Collider = object.m_Collider;
		m_ParticleSystem = object.m_ParticleSystem;
		m_Animation = object.m_Animation;
		m_Audio = object.m_Audio;
		m_CharacterController = object.m_CharacterController;
		m_AIController = object.m_AIController;

		ExceptionHandler::Handle(GameObjectContainer::Insert(*this, this->m_KEY));
	}

	void GameObject::RemoveComponent(ComponentType type)
	{
		switch (type)
		{
		case ComponentType::Mesh: DeleteComponent(m_Mesh); m_Mesh = UNDEF_PTR; break;
		case ComponentType::Camera: DeleteComponent(m_Camera); m_Camera = UNDEF_PTR;  break;
		case ComponentType::RigidBody: DeleteComponent(m_RigidBody); m_RigidBody = UNDEF_PTR; break;
		case ComponentType::Collider: DeleteComponent(m_Collider); m_Collider = UNDEF_PTR; break;
		case ComponentType::ParticleSystem: DeleteComponent(m_ParticleSystem); m_ParticleSystem = UNDEF_PTR; break;
		case ComponentType::Animation: DeleteComponent(m_Animation); m_Animation = UNDEF_PTR; break;
		case ComponentType::Audio: DeleteComponent(m_Audio); m_Audio = UNDEF_PTR; break;
		case ComponentType::CharacterController: DeleteComponent(m_CharacterController); m_CharacterController = UNDEF_PTR; break;
		case ComponentType::AIController: DeleteComponent(m_AIController); m_AIController = UNDEF_PTR; break;

		default: SV_CORE_INFO("Transform component cant be removed"); break;
		}
	}

	////////////////////////////////////////////////////////////
	// Additional functions
	////////////////////////////////////////////////////////////
	void DeleteComponent(IComponent* component)
	{
		if (component != UNDEF_PTR)
		{
			delete component;
			component = UNDEF_PTR;
		}

		return;
	}
}
