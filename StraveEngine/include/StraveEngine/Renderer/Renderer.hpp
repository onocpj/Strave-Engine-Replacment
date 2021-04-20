#pragma once

#include <StraveEngine/System/DataTypes.hpp>


namespace sf
{
	class Drawable;
	class RenderWindow;
}
namespace Strave
{
	struct Exception;
	class Mesh;
	class GameObject;
	class UserInterface;
	class GameObjectContainer;
	class Animation;
	class Camera;

	class Renderer final
	{
	public:
		static void Create(void);
		static Exception Delete(void);
		static void RenderScene(void);
		static sf::RenderWindow& GetGameWindow(void);
		static sf::RenderWindow& GetSceneWindow(void);
		static const GameObject* PullObjectFromContainer(Uint64 key);
		static const UserInterface* PullUserInterfaceFromContainer(Uint64 key);
		static const Animation* PullAnimationFromContainer(Uint64 key);
		static Camera* PullCameraFromContainer(Uint64 key);
		inline static void Draw(const Mesh& mesh) { RenderMesh(mesh); } // Instead of Mesh class, there should be Image class

	private:
		Renderer() = default;
		~Renderer() = default;
		Renderer(const Renderer&) = delete;

		static void RenderMesh(const Mesh& mesh);

	private:
		static Renderer* s_Renderer;
	};
}
