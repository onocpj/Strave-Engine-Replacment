#pragma once

#include "StraveEngine/System/Export.hpp"
#include "StraveEngine/System/WindowResolution.hpp"
#include "StraveEngine/System/WindowFramerate.hpp"
#include <StraveEngine/System/UndefinedDataTypes.hpp>
#include <StraveEngine/System/DataTypes.hpp>
#include <StraveEngine/Renderer/Renderer.hpp>

#include <functional>
#include <string>


#define SW_WINDOW_RUNNING !UNDEF_BOOL


namespace sf
{
	class Event;
	class VideoMode;
	class RenderWindow;
}
namespace Strave
{
	struct Exception;
	class WindowResolution;
	class WindowFramerate;

	enum class WindowType
	{
		GameWindow = 0,
		SceneWindow
	};

	class STRAVE_SYSTEM_API Window final
	{
	public:
		typedef std::function<void(void)> OnEvent;
		struct SandboxEvent
		{
			OnEvent OnStart;
			OnEvent OnUpdate;
			OnEvent OnEnd;
		};

	public:
		Window(std::string title, const WindowResolution& resolution, const SandboxEvent& sandboxEvent);
		Window(const Window&) = delete;

		inline void SetTitle(std::string title) { m_WindowTitle = title; }
		inline void SetResolition(WindowResolution resolution) { m_WindowResolution = resolution; }
		void SetFramerateCap(Uint64 cap);
		inline std::string GetTitle(void) const { return m_WindowTitle; }
		inline const WindowResolution& GetResolution(void) const { return m_WindowResolution; }
		inline const Uint64 GetFramerateCap(void) const { return m_WindowFramerate.GetFramerateCap(); }

		static Exception Execute(Window& window);
		static Exception Delete(Window*& window);

	private:
		~Window();
		void Init(void);

		friend sf::RenderWindow& Renderer::GetSceneWindow(void);
		friend sf::RenderWindow& Renderer::GetGameWindow(void);

		friend state_t WindowExecuted(const Window& window);
		friend Exception OpenWindow(Window& window);
		friend void AssignToExecution(Window& window);

	protected:
		static Window*		s_GameWindow;
		static Window*		s_SceneWindow; // Needs to be implemented (Scene editor window)

	private:
		std::string			m_WindowTitle;
		WindowResolution	m_WindowResolution;
		WindowFramerate		m_WindowFramerate;
		SandboxEvent		m_SandboxEvents;

		sf::Event*			m_SFEvent;
		sf::VideoMode*		m_SFVideoMode;
		sf::RenderWindow*	m_SFGameRenderWindow;
		sf::RenderWindow*	m_SFSceneRenderWindow;
	};
}

