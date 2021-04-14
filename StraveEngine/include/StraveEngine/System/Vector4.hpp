#pragma once

#include <StraveEngine/System/Export.hpp>
#include <StraveEngine/System/Vector2.hpp>


namespace Strave 
{
	template<typename Type> class STRAVE_SYSTEM_API Vector4
	{
	public:
		inline Vector4() = default;
		inline Vector4(Vector2<Type> min, Vector2<Type> max) : m_Min(min), m_Max(max) {}
		inline ~Vector4() = default;

		Vector2<Type> m_Min;
		Vector2<Type> m_Max;
	};

	template<typename Type>
	inline Vector4<Type> operator +=(Vector4<Type>& left, const Vector4<Type>& right) 
	{
		left.m_Min.x += right.m_Min.x;
		left.m_Min.y += right.m_Min.y;
		left.m_Max.x += right.m_Max.x;
		left.m_Max.y += right.m_Max.y;

		return left;
	}

	template<typename Type>
	inline Vector4<Type> operator +(const Vector4<Type>& left, const Vector4<Type>& right) 
	{

		return Vector4<Type>(
			Vector2<Type>(left.m_Min.x + right.m_Min.x, left.m_Min.y + right.m_Min.y),
			Vector2<Type>(left.m_Max.x + right.m_Max.x, left.m_Max.y + right.m_Max.y)
			);
	}

	template<typename Type>
	inline Vector4<Type> operator -=(Vector4<Type>& left, const Vector4<Type>& right) 
	{
		left.m_Min.x -= right.m_Min.x;
		left.m_Min.y -= right.m_Min.y;
		left.m_Max.x -= right.m_Max.x;
		left.m_Max.y -= right.m_Max.y;

		return left;
	}

	template<typename Type>
	inline Vector4<Type> operator -(const Vector4<Type>& left, const Vector4<Type>& right)
	{
		return Vector4<Type>(
			Vector2<Type>(left.m_Min.x - right.m_Min.x, left.m_Min.y - right.m_Min.y),
			Vector2<Type>(left.m_Max.x - right.m_Max.x, left.m_Max.y - right.m_Max.y)
			);
	}

	template<typename Type>
	inline Vector4<Type> operator *=(const Vector4<Type>& left, Type right) 
	{
		left.m_Min.x *= right;
		left.m_Min.y *= right;
		left.m_Max.x *= right;
		left.m_Max.y *= right;

		return left;
	}

	template<typename Type>
	inline Vector4<Type> operator *(const Vector4<Type>& left, Type right) 
	{
		return Vector4<Type>(
			Vector2<Type>(left.m_Min.x * right, left.m_Min.y * right),
			Vector2<Type>(left.m_Max.x * right, left.m_Max.y * right)
			);
	}

	template<typename Type>
	inline Vector4<Type> operator *(Type left, const Vector4<Type>& right) 
	{
		return Vector4<Type>(
			Vector2<Type>(left * right.m_Min.x, left * right.m_Min.y),
			Vector2<Type>(left * right.m_Max.x, left * right.m_Max.y)
			);
	}

	template<typename Type>
	inline Vector4<Type> operator /=(const Vector4<Type>& left, Type right) 
	{
		left.m_Min.x /= right;
		left.m_Min.y /= right;
		left.m_Max.x /= right;
		left.m_Max.y /= right;

		return left;
	}

	template<typename Type>
	inline Vector4<Type> operator /(const Vector4<Type>& left, Type right) 
	{
		return Vector4<Type>(
			Vector2<Type>(left.m_Min.x / right, left.m_Min.y / right),
			Vector2<Type>(left.m_Max.x / right, left.m_Max.y / right)
			);
	}

	template<typename Type>
	inline Vector4<Type> operator ==(const Vector4<Type>& left, const Vector4<Type>& right) 
	{
		return ((left.m_Min.x == right.m_Min.x) && (left.m_Min.y == right.m_Min.y)) &&
			((left.m_Max.x == right.m_Max.x) && (left.m_Max.y == right.m_Max.y));
	}

	template<typename Type>
	inline Vector4<Type> operator !=(const Vector4<Type>& left, const Vector4<Type>& right) 
	{
		return ((left.m_Min.x == right.m_Min.x) && (left.m_Min.y == right.m_Min.y)) ||
			((left.m_Max.x == right.m_Max.x) && (left.m_Max.y == right.m_Max.y));
	}

	typedef Vector4<float>			Vector4f;
	typedef Vector4<double>			Vector4d;
	typedef Vector4<int>			Vector4i;
	typedef Vector4<unsigned int>	Vector4u;
}
