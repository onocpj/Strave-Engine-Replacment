#pragma once

#include <StraveEngine/System/DataTypes.hpp>
#include <StraveEngine/System/UndefinedDataTypes.hpp>


#define WF_NO_CAP	UNDEF_UINT


namespace Strave
{
	class WindowFramerate final
	{
	public:
		WindowFramerate() = default;
		WindowFramerate(Uint64 cap) : m_FramerateCap(cap) {};
		~WindowFramerate() = default;
		WindowFramerate(const WindowFramerate&) = default;

		inline void SetFramerateCap(Uint64 cap) { m_FramerateCap = cap; }
		inline Uint64 GetFramerateCap(void) const { return m_FramerateCap; }

	private:
		Uint64 m_FramerateCap;
	};
}

