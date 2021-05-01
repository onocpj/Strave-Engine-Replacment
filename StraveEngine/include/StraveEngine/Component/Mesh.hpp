#pragma once

#include <StraveEngine/Element/Sprite.hpp>
#include <StraveEngine/System/Export.hpp>
#include <StraveEngine/Component/IComponent.hpp>
#include <StraveEngine/System/UndefinedDataTypes.hpp>

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
	class Texture;
	class Transform;

	class STRAVE_COMPONENT_API Mesh final : public IComponent
	{
	public:
		Mesh(Transform* transforms);
		Mesh(Transform* transforms, std::string name);
		Mesh(Transform* transforms, Sprite& sprite, std::string name = EMPTY_STR);
		Mesh(Transform* transforms, Texture& texture, std::string name = EMPTY_STR);
		Mesh(Transform* transforms, Sprite& sprite, Texture& texture, std::string name = EMPTY_STR);
		Mesh(const Mesh& mesh);
		~Mesh() = default;

		inline ComponentType GetComponentType(void) const override final { return ComponentType::Mesh; }
		inline Sprite& GetSprite(void) const { return *m_Sprite; }
		inline Texture& GetTexture(void) const { return *m_Texture; }
		void UpdateTexture(const Texture& texture);
		void SelectMesh(Sprite& sprite);
		void ApplyTexture(Texture& texture);
		void RemoveTexture(void);

	private:
		inline Sprite& GetCorrectSprite(void) const { return *static_cast<Sprite*>(m_Sprite->GetInstance()); }

	private:
		Transform*	m_Transforms;
		Sprite*		m_Sprite;
		Texture*	m_Texture;
	};
}
