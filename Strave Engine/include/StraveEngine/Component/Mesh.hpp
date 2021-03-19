#pragma once

#include <StraveEngine/System/Export.hpp>
#include <StraveEngine/Component/IComponent.hpp>
#include <StraveEngine/System/UndefinedDataTypes.hpp>
#include <StraveEngine/Element/ISprite.hpp>

#include <string>


namespace sf
{
	class Texture;
	class Sprite;
	class RectangleSprite;
	class Transformable;
}
namespace Strave
{
	class IElement;
	class Sprite;
	class RectangleSprite;
	class Texture;
	class GameObject;

	enum class STRAVE_COMPONENT_API MeshType
	{
		Sprite = 0,
		RectangleSprite,
		Circle,				// Not implemented yet
		Line,				// Not implemented yet
		Complex				// Not implemented yet
	};

	class STRAVE_COMPONENT_API Mesh final : public IComponent
	{
	public:
		Mesh(GameObject* object);
		Mesh(GameObject* object, std::string name);
		Mesh(GameObject* object, ISprite& sprite, std::string name = EMPTY_STR);
		Mesh(GameObject* object, Texture& texture, std::string name = EMPTY_STR);
		Mesh(GameObject* object, ISprite& sprite, Texture& texture, std::string name = EMPTY_STR);
		~Mesh() = default;
		Mesh(const Mesh& copy);

		inline ComponentType GetComponentType(void) const override final { return ComponentType::Mesh; }
		inline MeshType GetMeshType(void) const { return m_Type; }
		template<typename T> inline T& GetSprite(void) const
		{
			switch (m_Type) 
			{
			case MeshType::Sprite: return *static_cast<Sprite*>(m_Sprite->GetInstance()); break;
			case MeshType::RectangleSprite: return *static_cast<RectangleSprite*>(m_Sprite->GetInstance()); break;
			default: break;
			}
		}
		template<> inline Sprite& GetSprite(void) const { return *static_cast<Sprite*>(m_Sprite->GetInstance()); }
		template<> inline RectangleSprite& GetSprite(void) const { return *static_cast<RectangleSprite*>(m_Sprite->GetInstance()); }
		ISprite& GetSprite(void) const { return *m_Sprite; }
		inline Texture& GetTexture(void) const { return *m_Texture; }
		void SelectMesh(ISprite& sprite);
		void ApplyTexture(Texture& texture);
		void RemoveTexture(void);

	private:
		GameObject* m_GameObject;
		MeshType	m_Type;
		ISprite*	m_Sprite;
		Texture*	m_Texture;
	};
}
