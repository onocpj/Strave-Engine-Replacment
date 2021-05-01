#pragma once

#include <StraveEngine/System/Export.hpp>
#include <StraveEngine/System/ICollectable.hpp>
#include <StraveEngine/Entity/Object.hpp>


namespace Strave
{
	enum class STRAVE_COMPONENT_API ComponentType
	{
		Transform = 0,
		Mesh,
		Image,
		Camera,
		RigidBody,
		Collider,
		ParticleSystem,
		Animation,
		Audio,
		CharacterController,
		AIController
	};

	class STRAVE_COMPONENT_API IComponent abstract : public Object
	{
	public:
		virtual ~IComponent() = default;

		virtual ComponentType GetComponentType(void) const = 0;

	protected:
		IComponent() = default;
		IComponent(std::string name);
		IComponent(const IComponent&) = default;
	};
}

