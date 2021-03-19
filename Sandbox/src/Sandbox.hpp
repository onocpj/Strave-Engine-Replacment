#pragma once

#include <StraveEngine/StraveEngine.hpp>

using namespace Strave;

namespace Sandbox
{
	class Game final : public Strave::Application
	{
	public:
		Game() = default;
		~Game() = default;
		Game(const Game&) = delete;

		virtual void OnStart(void) const override final;
		virtual void OnUpdate(void) const override final;
		virtual void OnEnd(void) const override final;
	};
}
