#pragma once


namespace Strave
{	
	struct Exception;

	class Scene final
	{
	public:
		static void Create(void);
		static Exception Delete(void);
		static void LoadDefaultScene(void);

	private:
		Scene() = default;
		Scene(Scene& scene) = delete;
		~Scene() = default;

		void ILoadDefaultScene(void) const;

	private:
		static Scene* s_Scene;
	};
}

