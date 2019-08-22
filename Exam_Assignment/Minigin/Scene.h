#pragma once
#include "SceneManager.h"
#include "RenderComponent.h"

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

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private:

		std::string mName{};
		std::vector < SceneObject*> mObjects{};

		static unsigned int idCounter; 
	};

}
