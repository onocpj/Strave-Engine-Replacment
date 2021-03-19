#pragma once

#include <StraveEngine/System/UndefinedDataTypes.hpp>
#include "StraveEngine/System/Export.hpp"

#include <chrono>
#include <thread>
#include <string>
#include <iostream>


#define TM_STEADY_SYSTEM_CLOCK_NOW		std::chrono::steady_clock::now()
#define TM_TO_MS(DURATION)				DURATION.count() * 1000.0f


namespace Strave
{
	class STRAVE_SYSTEM_API Timer final
	{
	public:
		inline ~Timer()
		{
			m_End = TM_STEADY_SYSTEM_CLOCK_NOW;
			m_Duration = m_End - m_Start;
			float ms = TM_TO_MS(m_Duration);

			std::cout << "[TIMER END]" << "[" << m_Title << "]" << "[" << ms << " ms]" << std::endl;
		}

		Timer(const Timer&) = delete;

		inline static Timer* Start(std::string title = UNDEF_STR)
		{
			return new Timer(title);
		}

		inline void Stop(void) const
		{
			this->~Timer();
		}

	private:
		inline Timer(std::string title)
			: m_Title(title), m_Duration(UNDEF_FLOAT), m_Start(TM_STEADY_SYSTEM_CLOCK_NOW)
		{
			std::cout << "[TIMER START]" << "[" << title << "]" << std::endl;
		}

	private:
		std::string m_Title;
		std::chrono::duration<float> m_Duration;
		std::chrono::time_point<std::chrono::steady_clock> m_Start;
		std::chrono::time_point<std::chrono::steady_clock> m_End;
	};

	typedef Timer* _Timer;
}

