#pragma once


#include <StraveEngine/System/Export.hpp>
#include <StraveEngine/System/Vector2.hpp>
#include <StraveEngine/Component/IComponent.hpp>
#include <StraveEngine/Element/RectangleSprite.hpp>


namespace Strave
{
	class RectangleSprite;
	class Transform;
	class Texture;

	class STRAVE_COMPONENT_API Image final : public IComponent
	{
	public:
		Image(Transform* transforms);
		Image(Transform* transforms, std::string name);
		Image(Transform* transforms, RectangleSprite& sprite, std::string name = EMPTY_STR);
		Image(Transform* transforms, Texture& texture, std::string name = EMPTY_STR);
		Image(Transform* transforms, RectangleSprite& sprite, Texture& texture, std::string name = EMPTY_STR);
		Image(const Image& image);
		~Image() = default;

		inline ComponentType GetComponentType(void) const override { return ComponentType::Image; };
		template<typename T> T& GetComponent(void) const;
		template<> inline Transform& GetComponent(void) const { return *m_Transforms; }
		inline RectangleSprite& GetSprite(void) const { return *m_Sprite; }
		inline Texture& GetTexture(void) const { return *m_Texture; }
		inline Vector2f GetNativeSize(void) const { return m_NativeSize; }
		void SetNativeSize(Vector2f nativeSize);
		void UpdateTexture(const Texture& texture);
		void SelectImage(RectangleSprite& image);
		void ApplyTexture(Texture& texture);
		void RemoveTexture(void);

	private:
		inline RectangleSprite& GetCorrectSprite(void) const { return *static_cast<RectangleSprite*>(m_Sprite->GetInstance()); }

	private:
		Transform*			m_Transforms;
		RectangleSprite*	m_Sprite;
		Texture*			m_Texture;
		Vector2f			m_NativeSize;
	};
}
