#include <SFML/Graphics/RenderWindow.hpp>

#include <StraveEngine/Renderer/Renderer.hpp>

#include <StraveEngine/System/Exception.hpp>
#include <StraveEngine/System/Window.hpp>
#include <StraveEngine/System/Log.hpp>
#include <StraveEngine/Component/Mesh.hpp>
#include <StraveEngine/Element/Sprite.hpp>
#include <StraveEngine/Element/RectangleSprite.hpp>
#include <StraveEngine/Entity/GameObjectContainer.hpp>
#include <StraveEngine/Entity/GameObject.hpp>
#include <StraveEngine/Entity/GameObject.hpp>
#include <StraveEngine/System/MapContainer.cpp>


namespace Strave
{
	Renderer* Renderer::s_Renderer;

	void Renderer::Create(void)
	{
		Renderer::s_Renderer = new Renderer();
	}

	Exception Renderer::Delete(void)
	{
		try 
		{
			delete Renderer::s_Renderer;
			Renderer::s_Renderer = nullptr;
		}
		catch (...)
		{
			return THROW__EXC_RNDR_DEL;
		}

		return NO_EXCEPTION;
	}

	void Renderer::RenderScene(void)
	{
		const GameObject* objectToRender = UNDEF_PTR;

		for (Int64 key = -1; key != (GameObjectContainer::GetOCSize() - 1); key++)
		{
			objectToRender = Renderer::PullObjectFromContainer((Uint64)key);

			if(objectToRender != UNDEF_PTR)
				Renderer::RenderMesh(objectToRender->GetComponent<Mesh>());
		}
	}

	sf::RenderWindow& Renderer::GetGameWindow(void)
	{
		return *Window::s_GameWindow->m_SFGameRenderWindow;
	}

	sf::RenderWindow& Renderer::GetSceneWindow(void)
	{
		return *Window::s_GameWindow->m_SFGameRenderWindow;
	}

	const GameObject* Renderer::PullObjectFromContainer(Uint64 key)
	{
		return GameObjectContainer::s_GameObjectContainer->Next(key);
	}

	void Renderer::RenderMesh(const Mesh& mesh)
	{
		MeshType meshType = mesh.GetMeshType();

		if (meshType == MeshType::Sprite) 
		{
			Sprite* sprite = &mesh.GetSprite<Sprite>();
			Renderer::GetGameWindow().draw(*sprite);
		}
		else
			Renderer::GetGameWindow().draw(mesh.GetSprite<RectangleSprite>());
	}
}
