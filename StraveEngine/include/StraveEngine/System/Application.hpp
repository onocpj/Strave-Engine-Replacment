#pragma once

#include <StraveEngine/System/Export.hpp>


namespace Strave
{
	class STRAVE_SYSTEM_API Application abstract
	{
	public:
		Application() = default;
		~Application() = default;
		Application(const Application&) = delete;

		virtual int Execute(void) const;
		virtual int ExecuteEditor(void) const; // Needs to be implemented (Scene editor window)

		virtual void OnStart(void) const = 0;
		virtual void OnUpdate(void) const = 0;
		virtual void OnEnd(void) const = 0;
	};
}