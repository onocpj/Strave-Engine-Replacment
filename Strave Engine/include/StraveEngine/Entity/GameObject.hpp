#pragma once

#include <StraveEngine/System/Export.hpp>
#include <StraveEngine/System/DataTypes.hpp>
#include <StraveEngine/System/Log.hpp>
#include <StraveEngine/Entity/Object.hpp>
#include <StraveEngine/Component/IComponent.hpp>
#include <StraveEngine/Component/Transform.hpp>
#include <StraveEngine/Component/Mesh.hpp>
#include <StraveEngine/Component/CharacterController.hpp>


#define GO_KEY_UNASSIGNED	ERROR_TYPE


namespace Strave
{
	enum class ComponentType;
	class Camera;
	class RigidBody;
	class Collider;
	class ParticleSystem;
	class Animation;
	class Audio;
	class AIController;

	class STRAVE_ENTITY_API GameObject final : public Object
	{
	public:
		GameObject();
		GameObject(std::string name);
		~GameObject();
		GameObject(const GameObject& object);

		template<typename T> inline T& GetComponent(void) const;
		template<> inline Transform& GetComponent<Transform>(void) const { return *m_Transform; }
		template<> inline Mesh& GetComponent<Mesh>(void) const { return *m_Mesh; }
		//template<> inline Camera& GetComponent<Camera>(void) const { return *m_Camera; }
		//template<> inline RigidBody& GetComponent<RigidBody>(void) const { return *m_RigidBody; }
		//template<> inline Collider& GetComponent<Collider>(void) const { return *m_Collider; }
		//template<> inline ParticleSystem& GetComponent<ParticleSystem>(void) const { return *m_ParticleSystem; }
		//template<> inline Animation& GetComponent<Animation>(void) const { return *m_Animation; }
		//template<> inline Audio& GetComponent<Audio>(void) const { return *m_Audio; }
		template<> inline CharacterController& GetComponent<CharacterController>(void) const { return *m_CharacterController; }
		//template<> inline AIController& GetComponent<AIController>(void) const { return *m_AIController; }
		template<typename T> inline void AddComponent(void);
		template<> inline void AddComponent<Transform>(void) 
		{ 
			if (m_Transform == UNDEF_PTR)
				m_Transform = new Transform(this);
			else
				SV_CORE_INFO("function AddComponent<Transform> from GameObject: Object has already assigned transsform");
		}
		template<> inline void AddComponent<Mesh>(void) 
		{
			if (m_Mesh == UNDEF_PTR)
				m_Mesh = new Mesh(this);
			else
				SV_CORE_INFO("function AddComponent<Mesh> from GameObject: Object has already assigned mesh");
		}
		//template<> inline void AddComponent<Camera>(Camera& component) { m_Camera = &component; }
		//template<> inline void AddComponent<RigidBody>(RigidBody& component) { m_RigidBody = &component; }
		//template<> inline void AddComponent<Collider>(Collider& component) { m_Collider = &component; }
		//template<> inline void AddComponent<ParticleSystem>(ParticleSystem& component) { m_ParticleSystem = &component; }
		//template<> inline void AddComponent<Animation>(Animation& component) { m_Animation = &component; }
		//template<> inline void AddComponent<Audio>(Audio& component) { m_Audio = &component; }
		template<> inline void AddComponent<CharacterController>(void) 
		{ 
			if (m_CharacterController == UNDEF_PTR)
				m_CharacterController = new CharacterController(this);
			else
				SV_CORE_INFO("function AddComponent<CharacterController> from GameObject: Object has already assigned character controller");
		}
		//template<> inline void AddComponent<AIController>(AIController& component) { m_AIController = &component; }
		void RemoveComponent(ComponentType componentType);

	private:
		Uint64					m_KEY;
		Mesh*					m_Mesh;					
		Transform*				m_Transform;
		IComponent*				m_Camera;				// Not implemented yet
		IComponent*				m_RigidBody;			// Not implemented yet
		IComponent*				m_Collider;				// Not implemented yet
		IComponent*				m_ParticleSystem;		// Not implemented yet
		IComponent*				m_Animation;			// Not implemented yet
		IComponent*				m_Audio;				// Not implemented yet
		CharacterController*	m_CharacterController;  
		IComponent*				m_AIController;			// Not implemented yet
	};
}

