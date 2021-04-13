#include <StraveEngine/System/Window.hpp>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <StraveEngine/System/Log.hpp>
#include <StraveEngine/System/Exception.hpp>
#include <StraveEngine/System/ExceptionHandler.hpp>
#include <StraveEngine/Renderer/Renderer.hpp>
#include <StraveEngine/System/EngineClocks.hpp>
#include <StraveEngine/Scene/Scene.hpp>


namespace Strave
{
	Window* Window::s_GameWindow = UNDEF_PTR;
	Window* Window::s_SceneWindow = UNDEF_PTR;

	////////////////////////////////////////////////////////////
	/// Window
	////////////////////////////////////////////////////////////
	Window::Window(std::string title, const WindowResolution& resolution, const SandboxEvent& sandboxEvent) :
		m_WindowTitle(title),
		m_WindowResolution(resolution),
		m_WindowFramerate(WF_NO_CAP),
		m_SandboxEvents(sandboxEvent),
		m_SFEvent(UNDEF_PTR),
		m_SFVideoMode(UNDEF_PTR),
		m_SFGameRenderWindow(UNDEF_PTR),
		m_SFSceneRenderWindow(UNDEF_PTR)
	{
		Window::Init();
	}

	Window::~Window()
	{
		delete m_SFVideoMode;
		delete m_SFEvent;
		delete m_SFGameRenderWindow;
	}

	void Window::Init(void)
	{
		m_SFVideoMode = new sf::VideoMode(m_WindowResolution.GetWidth(), m_WindowResolution.GetHeight());
		m_SFGameRenderWindow = new sf::RenderWindow(*m_SFVideoMode, m_WindowTitle);
		m_SFEvent = new sf::Event();
	}

	void Window::SetFramerateCap(Uint64 cap)
	{
		m_WindowFramerate.SetFramerateCap(cap);
		m_SFGameRenderWindow->setFramerateLimit((unsigned int)cap);
	}

	Exception Window::Execute(Window& window)
	{
		if (!WindowExecuted(window)) {
			AssignToExecution(window);
			return OpenWindow(window);
		}
		
		return THROW__EXC_WIN_RUN;
	}

	Exception Window::Delete(Window*& window)
	{
		try {
			delete window;
			window = nullptr;
		}
		catch(...) 
		{
			return THROW__EXC_WIN_DEL;
		}

		return NO_EXCEPTION;
	}

	Exception OpenWindow(Window& window)
	{
		SV_CORE_INFO("Window opened");

		// Create scene
		Scene::Create();					// Call function to create default scene
		Scene::LoadDefaultScene();			// Call function to load default scene

		window.m_SandboxEvents.OnStart();	// Call function from sandbox that is executed at start of the application

		while (window.m_SFGameRenderWindow->isOpen())
		{
			window.m_SFGameRenderWindow->clear(sf::Color(0, 255, 0, 0));
			window.m_SandboxEvents.OnUpdate();	// Call function from sandbox that is executed each frame
			EngineClocks::Update();
			Renderer::RenderScene();
			window.m_SFGameRenderWindow->display();

			while (window.m_SFGameRenderWindow->pollEvent(*window.m_SFEvent))
			{
				if (window.m_SFEvent->type == sf::Event::Closed)
				{
					window.m_SFGameRenderWindow->close();
					window.m_SandboxEvents.OnEnd(); // Call function from sandbox that is executed upon end
					ExceptionHandler::Handle(Scene::Delete());

					SV_CORE_INFO("Window closed");
				}
			}
		}

		return NO_EXCEPTION;
	}

	state_t WindowExecuted(const Window& window)
	{
		if (Window::s_GameWindow != UNDEF_PTR)
			return true;
		else
			return false;
	}

	void AssignToExecution(Window& window)
	{
		Window::s_GameWindow = &window;
	}
}
