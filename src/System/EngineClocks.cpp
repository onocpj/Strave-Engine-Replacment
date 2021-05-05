#include <StraveEngine/System/EngineClocks.hpp>

#include <SFML/Window.hpp>


namespace Strave
{
	sf::Clock	EngineClocks::Clock;
	sf::Time	EngineClocks::Time;
	float		EngineClocks::DeltaTime = 0.0f;

	void EngineClocks::Update(void)
	{
		EngineClocks::Time = EngineClocks::Clock.getElapsedTime();
		EngineClocks::DeltaTime = (float)EngineClocks::Time.asSeconds(); // Use instead asSeconds()
		EngineClocks::Clock.restart();
	}
}
