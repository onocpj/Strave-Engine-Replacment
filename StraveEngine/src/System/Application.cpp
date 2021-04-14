#include <StraveEngine/System/Application.hpp>

#include <StraveEngine/System/Log.hpp>
#include <StraveEngine/System/Exception.hpp>
#include <StraveEngine/System/Window.hpp>
#include <StraveEngine/System/GarbageCollector.hpp>
#include <StraveEngine/System/ExceptionHandler.hpp>
#include <StraveEngine/Renderer/Renderer.hpp>
#include <StraveEngine/Entity/GameObjectContainer.hpp>
#include <StraveEngine/UI/UserInterfaceContainer.hpp>
#include <StraveEngine/Component/Camera/CameraContainer.hpp>
#include <StraveEngine/Component/Animation/AnimationContainer.hpp>


namespace Strave
{
	int Application::Execute(void) const
	{
		// ...My code...

		// Initialize Logger
		svlog::Log::Init( "CORE", "CLIENT",
			{ svlog::Color::Blue, svlog::Color::Gray, svlog::Color::Yellow, svlog::Color::Purple, svlog::Color::Red, },
			{ svlog::Color::Blue, svlog::Color::Gray, svlog::Color::Yellow, svlog::Color::Purple, svlog::Color::Red, }
		);

		GarbageCollector::Create();			// Initialize GarbageCollector
		GameObjectContainer::Create();		// Initialize GameObjectContainer
		UserInterfaceContainer::Create();	// Initialize userInterfaceContainer
		CameraContainer::Create();			// Initialize CameraContainer
		AnimationContainer::Create();		// Initialize AnimationContainer
		Renderer::Create();					// Initialize Renderer

		// Initialize Window
		WindowResolution Resolution = { 1280, 720 };
		Window::SandboxEvent Events = {
			std::bind(&Application::OnStart, this),
			std::bind(&Application::OnUpdate, this),
			std::bind(&Application::OnEnd, this)
		};
		Window* MainWindow = new Window("Strave Engine - Test", Resolution, Events);	// Create main window
		Window::Execute(*MainWindow);

		// Terminate application lambda
		auto TerminateApplication = [&](void) -> int {

			// Application termination functions passed to 
			// exception handler in case they threw exception
			ExceptionHandler::Pass(Window::Delete(MainWindow));
			ExceptionHandler::Pass(Renderer::Delete());
			ExceptionHandler::Pass(GameObjectContainer::Delete());
			ExceptionHandler::Pass(UserInterfaceContainer::Delete());
			ExceptionHandler::Pass(CameraContainer::Delete());
			ExceptionHandler::Pass(AnimationContainer::Delete());
			ExceptionHandler::Pass(GarbageCollector::SweepMemory());
			ExceptionHandler::Pass(GarbageCollector::Delete());
			ExceptionHandler::Pass(svlog::Log::Delete());

			// Handles all passed exceptions
			ExceptionHandler::HandleQueue();

			return 0;
		};

		return TerminateApplication();
	}

	int Application::ExecuteEditor(void) const // Needs to be implemented (Scene editor window)
	{
		// Now there is no editor window and developer have to implement
		// every engine element by writing code. In future engine allows
		// developer to open scene editor window that allows him to create
		// all engine elements with drag and drop 

		return 0;
	}
}