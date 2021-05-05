#include <StraveEngine/Element/Texture.hpp>

#include <StraveEngine/System/Log.hpp>
#include <StraveEngine/System/UndefinedDataTypes.hpp>


namespace Strave
{
	sf::Texture* Texture::s_EmptyTexture = new sf::Texture();

	Texture::Texture() :
		sf::Texture(),
		IElement()
	{}

	Texture::Texture(std::string name) :
		sf::Texture(),
		IElement(name)
	{}

	Texture* Texture::LoadTexture(const fpath_t filePath, std::string name)
	{
		Texture* texture = new Texture(name);

		if (texture->loadFromFile(filePath))
		{
			SV_CORE_TRACE("Texture loaded");
			return texture;
		}
		else
		{
			SV_CORE_WARN("function LoadTexture from Texture: Unable to load texture");
		}

		return UNDEF_PTR;
	}
}
