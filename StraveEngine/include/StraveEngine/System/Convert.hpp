#pragma once

#include <StraveEngine/System/Export.hpp>
#include <StraveEngine/System/Vector2.hpp>
#include <StraveEngine/System/Vector4.hpp>


namespace sf 
{
	template<typename Type> class Vector2;
	template<typename Type> class Vector3;
}
namespace Strave 
{
	class STRAVE_SYSTEM_API Convert abstract
	{
	public:
		Convert() = delete;
		~Convert() = delete;
		Convert(const Convert&) = delete;

	public:
		template<typename Type>
		inline static sf::Vector2<Type> ToVector2(const Vector2<Type>& vec2) 
		{
			return { vec2.x, vec2.y };
		}

		template<typename Type>
		inline static Vector2<Type> ToVector2(const sf::Vector2<Type>& vec2) 
		{
			return { vec2.x, vec2.y };
		}

		template<typename Type>
		inline static Vector2f ToVector2f(const sf::Vector2<Type>& vec2) 
		{
			return { (float)vec2.x, (float)vec2.y };
		}

		template<typename Type>
		inline static Vector2u ToVector2u(const sf::Vector2<Type>& vec2)
		{
			return { (unsigned int)vec2.x, (unsigned int)vec2.y };
		}

		template<typename Type>
		inline static Vector2i ToVector2i(const sf::Vector2<Type>& vec2) 
		{
			return { (int)vec2.x, (int)vec2.y };
		}

		template<typename Type>
		inline static Vector2f ToVector2f(const Vector2<Type>& vec2) 
		{
			return { (float)vec2.x, (float)vec2.y };
		}

		template<typename Type>
		inline static Vector2u ToVector2u(const Vector2<Type>& vec2)
		{
			return { (unsigned int)vec2.x, (unsigned int)vec2.y };
		}

		template<typename Type>
		inline static Vector2i ToVector2i(const Vector2<Type>& vec2) 
		{
			return { (int)vec2.x, (int)vec2.y };
		}
	};
}
