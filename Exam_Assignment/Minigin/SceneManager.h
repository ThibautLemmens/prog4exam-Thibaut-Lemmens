#pragma once
#include "Singleton.h"

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		SceneManager() { CreateScene("Presistend"); };

		Scene* CreateScene(const std::string& name);

		void Update();
		void Render();

		Scene* PresistendScene() { return &mScenes[0]; };


	private:
		std::vector<Scene> mScenes;
	};

}
