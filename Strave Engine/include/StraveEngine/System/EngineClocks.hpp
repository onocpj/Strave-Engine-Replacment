#pragma once

#include <StraveEngine/System/Export.hpp>
#include <StraveEngine/System/Exception.hpp>


namespace sf
{
	class Clock;
	class Time;
}
namespace Strave
{
	class Window;

	class STRAVE_SYSTEM_API EngineClocks abstract final
	{
	private: 
		friend Exception OpenWindow(Window& window);

	private:
		EngineClocks() = delete;
		~EngineClocks() = delete;
		EngineClocks(const EngineClocks&) = delete;

	public:
		static float DeltaTime;

	protected:
		static void Update(void);

	private:
		static sf::Clock Clock;
		static sf::Time	Time;
	};
}
