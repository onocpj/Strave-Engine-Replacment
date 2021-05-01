#pragma once

#include <SFML/Graphics/Texture.hpp>

#include <StraveEngine/System/Export.hpp>
#include <StraveEngine/System/DataTypes.hpp>
#include <StraveEngine/System/UndefinedDataTypes.hpp>
#include <StraveEngine/Element/IElement.hpp>

#include <string>


namespace Strave
{
	class STRAVE_GRAPHICS_API Texture final : public sf::Texture, public IElement
	{
	public:
		Texture();
		Texture(std::string name);
		~Texture() = default;
		Texture(const Texture&) = default;

		inline ElementType GetElementType(void) const override final { return ElementType::Texture; }
		inline static Texture& GetEmpty(void) { return static_cast<Texture&>(*s_EmptyTexture); }
		static Texture* LoadTexture(const fpath_t filePath, std::string name = EMPTY_STR);
		inline static bool IsEmpty(const Texture* texture) { return texture == UNDEF_PTR ? true : false; }
		inline bool IsEmpty(void) const { return this == UNDEF_PTR ? true : false; }

	private:
		static sf::Texture* s_EmptyTexture;
	};
}

