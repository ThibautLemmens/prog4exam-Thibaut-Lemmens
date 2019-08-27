#pragma once
#include "Singleton.h"

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		SceneManager() { CreateScene("Presistend"); };
		~SceneManager();
		Scene* CreateScene(const std::string& name);
		void AddScene(Scene* scene);
		void Update();
		void RenderUpdate();
		void Render();
		void Empty();

		Scene* PresistendScene() { return mScenes[0]; };


	private:
		std::vector<Scene*> mScenes;
	};

}
