#include <StraveEngine/Scene/Scene.hpp>

#include <StraveEngine/Component/Camera/Camera.hpp>
#include <StraveEngine/System/Exception.hpp>


namespace Strave 
{
	Scene* Scene::s_Scene;

	void Scene::Create(void)
	{
		Scene::s_Scene = new Scene();
	}

	Exception Scene::Delete(void)
	{
		try
		{
			delete Scene::s_Scene;
			Scene::s_Scene = nullptr;
		}
		catch (...)
		{
			return THROW__EXC_SCENE_DEL;
		}

		return NO_EXCEPTION;
	}

	void Scene::LoadDefaultScene(void)
	{
		s_Scene->ILoadDefaultScene();
	}

	void Scene::ILoadDefaultScene(void) const
	{
		Camera* defaultCamera = new Camera("Main camera");
	}
}
