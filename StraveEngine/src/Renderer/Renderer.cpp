#include <SFML/Graphics/RenderWindow.hpp>

#include <StraveEngine/Renderer/Renderer.hpp>

#include <StraveEngine/System/Exception.hpp>
#include <StraveEngine/System/Window.hpp>
#include <StraveEngine/System/Log.hpp>
#include <StraveEngine/Utility/Array.hpp>
#include <StraveEngine/Component/Mesh.hpp>
#include <StraveEngine/Element/Sprite.hpp>
#include <StraveEngine/Element/RectangleSprite.hpp>
#include <StraveEngine/Entity/GameObjectContainer.hpp>
#include <StraveEngine/Entity/GameObject.hpp>
#include <StraveEngine/UI/UserInterface.hpp>
#include <StraveEngine/UI/UserInterfaceContainer.hpp>
#include <StraveEngine/System/MapContainer.cpp>
#include <StraveEngine/Component/Animation/Animation.hpp>
#include <StraveEngine/Component/Animation/AnimationContainer.hpp>
#include <StraveEngine/Component/Camera/CameraContainer.hpp>
#include <StraveEngine/Component/Camera/Camera.hpp>


namespace Strave
{
	Renderer* Renderer::s_Renderer;

	enum ContainerType
	{
		GameObjectContainer = 0,
		UserInterfaceContainer
	};

	struct SelectedContainer
	{
		ContainerType type;
		Uint64 size;
	};

	void Renderer::Create(void)
	{
		Renderer::s_Renderer = new Renderer();
	}

	SelectedContainer SelectLargerContainer(SelectedContainer* containers, Uint64 conNum);

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
		const UserInterface* userInterface = UNDEF_PTR;
		Camera* cameraToUpdate = UNDEF_PTR;

		Uint64 objectContainerSize = GameObjectContainer::GetObjectContainerSize();
		// Fix: -1 Should not be there. There is some kind of problem, 
		// where each time there is allocated one object that should not be there
		Uint64 userInterfaceContainerSize = UserInterfaceContainer::GetUserInterfaceContainerSize() - 1; 

		Uint64 containerSizes[] = {
			objectContainerSize,
			userInterfaceContainerSize
		};

		Uint64 largerContainerSize = Array::FindLargest(containerSizes, 2);

		for (Uint64 key = -1; key != largerContainerSize - 1; key++)
		{
			if (key != (objectContainerSize - 1))
			{
				// Render objects into scene
				objectToRender = Renderer::PullObjectFromContainer((Uint64)key);

				if (objectToRender != UNDEF_PTR)
				{
					Animation::Update(*objectToRender);
					Renderer::RenderMesh(objectToRender->GetComponent<Mesh>());
				}
			}
			if (key != (userInterfaceContainerSize - 1))
			{
				// Optimalize: We dont need to cycle whole map of ui, because some of the ui can be
				// hided on screen, so we dont need to iterate through these

				// Render user interface into scene
				userInterface = Renderer::PullUserInterfaceFromContainer((Uint64)key);

				if (userInterface != UNDEF_PTR)
					if (userInterface->IsVisible())
							Renderer::RenderMesh(userInterface->GetComponent<Mesh>());
			}
		}

		// Render cameras into scene
		Uint64 cameraContainerSize = CameraContainer::GetCameraContainerCSize();
		if (cameraContainerSize == 1)
		{
			cameraToUpdate = Renderer::PullCameraFromContainer((Uint64)(-1));

			if (cameraToUpdate != UNDEF_PTR)
			{
				Renderer::GetGameWindow().setView(cameraToUpdate->GetCameraView());
				cameraToUpdate->Update();
			}
		}
		else if (cameraContainerSize > 1)
		{
			for (Int64 key = -1; key != cameraContainerSize - 1; key++)
			{
				cameraToUpdate = Renderer::PullCameraFromContainer((Uint64)key);

				if (cameraToUpdate != UNDEF_PTR)
				{
					Renderer::GetGameWindow().setView(cameraToUpdate->GetCameraView());
					cameraToUpdate->Update();
				}
			}
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

	const UserInterface* Renderer::PullUserInterfaceFromContainer(Uint64 key)
	{
		return UserInterfaceContainer::s_UserInterfaceContainer->Next(key);
	}

	const Animation* Renderer::PullAnimationFromContainer(Uint64 key)
	{
		return AnimationContainer::s_AnimationContainer->Next(key);
	}

	Camera* Renderer::PullCameraFromContainer(Uint64 key)
	{
		return CameraContainer::s_CameraContainer->Next(key);
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

	////////////////////////////////////////////////////////////
	/// Additional renderer functions
	////////////////////////////////////////////////////////////
	SelectedContainer SelectLargerContainer(SelectedContainer* containers, Uint64 conNum)
	{
		SelectedContainer largest = containers[0];

		for (Uint64 i = 0; i != conNum; i++)
			if (largest.size < containers[i].size)
				largest = containers[i];

		return largest;
	}
}
