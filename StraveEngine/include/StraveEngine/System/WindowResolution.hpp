#pragma once

#include <StraveEngine/System/Export.hpp>
#include <StraveEngine/System/DataTypes.hpp>


namespace Strave
{
	class STRAVE_SYSTEM_API WindowResolution final
	{
	public:
		inline WindowResolution(Uint16 width, Uint16 height) : 
			m_Width(width), m_Height(height)
		{}
		~WindowResolution() = default;
		WindowResolution(const WindowResolution&) = default;

		inline Uint16 GetWidth() const { return m_Width; }
		inline Uint16 GetHeight() const { return m_Height; }

	private:
		Uint16 m_Width;
		Uint16 m_Height;
	};
}

