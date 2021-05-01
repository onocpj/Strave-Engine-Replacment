#pragma once

#include <StraveEngine/Component/Mesh.hpp>
#include <StraveEngine/Component/Animation/Animation.hpp>
#include <StraveEngine/Component/IComponent.hpp>
#include <StraveEngine/Component/Transform.hpp>
#include <StraveEngine/Component/CharacterController.hpp>
#include <StraveEngine/Component/Camera/Camera.hpp>
#include <StraveEngine/System/Export.hpp>
#include <StraveEngine/System/DataTypes.hpp>
#include <StraveEngine/System/Log.hpp>
#include <StraveEngine/Entity/Object.hpp>


#define GO_KEY_UNASSIGNED	ERROR_TYPE


namespace Strave
{
	enum class ComponentType;
	class RigidBody;
	class Collider;
	class ParticleSystem;
	class Audio;
	class AIController;

	class STRAVE_ENTITY_API GameObject final : public Object
	{
	public:
		GameObject();
		GameObject(std::string name);
		GameObject(const GameObject& object);
		~GameObject() = default;

		inline const Uint64& GetKey(void) const { return m_KEY; }
		template<typename T> inline T& GetComponent(void) const;
		template<> inline Transform& GetComponent<Transform>(void) const { return *m_Transform; }
		template<> inline Mesh& GetComponent<Mesh>(void) const { return *m_Mesh; }
		template<> inline Camera& GetComponent<Camera>(void) const { return *m_Camera; }
		template<> inline Animation& GetComponent<Animation>(void) const { return *m_Animation; }
		//template<> inline RigidBody& GetComponent<RigidBody>(void) const { return *m_RigidBody; }
		//template<> inline Collider& GetComponent<Collider>(void) const { return *m_Collider; }
		//template<> inline ParticleSystem& GetComponent<ParticleSystem>(void) const { return *m_ParticleSystem; }
		//template<> inline Audio& GetComponent<Audio>(void) const { return *m_Audio; }
		template<> inline CharacterController& GetComponent<CharacterController>(void) const { return *m_CharacterController; }
		//template<> inline AIController& GetComponent<AIController>(void) const { return *m_AIController; }
		template<typename T> inline void AddComponent(void);
		template<> inline void AddComponent<Transform>(void) 
		{ 
			if (m_Transform == UNDEF_PTR)
			{
				m_Transform = new Transform(&this->m_Mesh->GetSprite());
				return;
			}
			else
				SV_CORE_INFO("function AddComponent<Transform> from GameObject: Object has already assigned transsform");
		}
		template<> inline void AddComponent<Mesh>(void) 
		{
			if (m_Mesh == UNDEF_PTR)
			{
				m_Mesh = new Mesh(this->m_Transform);
				return;
			}
			else
				SV_CORE_INFO("function AddComponent<Mesh> from GameObject: Object has already assigned mesh");
		}
		template<> inline void AddComponent<Camera>(void) 
		{ 
			if (m_Camera == UNDEF_PTR)
			{
				m_Camera = new Camera();
				m_Camera->AssignTransforms(*this->m_Transform);
				return;
			}
			else
				SV_CORE_INFO("function AddComponent<Camera> from GameObject: Object has already assigned camera");
		}
		//template<> inline void AddComponent<RigidBody>(RigidBody& component) { m_RigidBody = &component; }
		//template<> inline void AddComponent<Collider>(Collider& component) { m_Collider = &component; }
		//template<> inline void AddComponent<ParticleSystem>(ParticleSystem& component) { m_ParticleSystem = &component; }
		//template<> inline void AddComponent<Audio>(Audio& component) { m_Audio = &component; }
		template<> inline void AddComponent<CharacterController>(void) 
		{ 
			if (m_CharacterController == UNDEF_PTR) 
			{
				m_CharacterController = new CharacterController(this);
				return;
			}
			else
				SV_CORE_INFO("function AddComponent<CharacterController> from GameObject: Object has already assigned character controller");
		}
		//template<> inline void AddComponent<AIController>(AIController& component) { m_AIController = &component; }
		template<typename T> inline void AssignComponent(T& component);
		template<> inline void AssignComponent(Camera& camera)
		{
			if (m_Camera == UNDEF_PTR) 
			{
				m_Camera = &camera;
				m_Camera->AssignTransforms(*this->m_Transform);

				return;
			}
			else
				SV_CORE_INFO("function AssignComponent<Camera> from GameObject: Object has already assigned camera");
		}
		template<> inline void AssignComponent(Animation& animation)
		{
			if (m_Animation == UNDEF_PTR)
			{
				m_Animation = &animation;
				m_Animation->AssignObject(*this);

				return;
			}
			else
				SV_CORE_INFO("function AssignComponent<Animation> from GameObject: Object has already assigned animation");
		}
		template<typename T> inline bool HaveAssignComponent(void) const;
		template<> inline bool HaveAssignComponent<Camera>(void) const
		{
			return m_Camera == UNDEF_PTR ? false : true;
		}
		template<> inline bool HaveAssignComponent<Animation>(void) const
		{
			return m_Animation == UNDEF_PTR ? false : true;
		}
		template<typename T> inline void UnassignComponent(void);
		template<> inline void UnassignComponent<Camera>(void)
		{
			m_Camera = UNDEF_PTR;
		}
		template<> inline void UnassignComponent<Animation>(void)
		{
			m_Animation = UNDEF_PTR;
		}
		void RemoveComponent(ComponentType componentType);

	private:
		Uint64					m_KEY;
		Mesh*					m_Mesh;					
		Transform*				m_Transform;
		Camera*					m_Camera;				
		IComponent*				m_RigidBody;			// Not implemented yet
		IComponent*				m_Collider;				// Not implemented yet
		IComponent*				m_ParticleSystem;		// Not implemented yet
		Animation*				m_Animation;			
		IComponent*				m_Audio;				// Not implemented yet
		CharacterController*	m_CharacterController;  
		IComponent*				m_AIController;			// Not implemented yet
	};
}

