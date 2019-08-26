#pragma once
#include "SceneManager.h"
#include "RenderComponent.h"
#include "SceneRenderer.h"
namespace dae
{
	class SceneObject;
	class Scene
	{
		friend Scene* SceneManager::CreateScene(const std::string& name);
		friend SceneManager::SceneManager();
	public:
		void Add(SceneObject* object);
		Scene() { mSceneRenderer = new SceneRenderer(); };

		void Update();
		SceneRenderer* GetSceneRenderer() { return mSceneRenderer; };


		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;
	protected:
		SceneRenderer* mSceneRenderer;
		std::vector < SceneObject*> mObjects{};
	private:

		std::string mName{};
		static unsigned int idCounter; 
	};

}
