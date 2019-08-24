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
		Scene() = default;

		void Update();
		SceneRenderer* GetSceneRenderer() const { return mSceneRenderer; };


		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private:

		std::string mName{};
		std::vector < SceneObject*> mObjects{};
		SceneRenderer* mSceneRenderer;
		static unsigned int idCounter; 
	};

}
