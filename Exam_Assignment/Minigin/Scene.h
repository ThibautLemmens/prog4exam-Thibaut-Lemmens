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
		void Add(const std::shared_ptr<SceneObject>& object);

		void Update();

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

		void Render()
		{
			for (RenderComponent& RC : m_RenderComponentes)
			{
				RC.Render();
			}
		};

		RenderComponent* GetComponent(TransformComponent* transform)
		{
			m_RenderComponentes.push_back(RenderComponent(transform));
			return &m_RenderComponentes.back();
		}

	private:
		std::vector<RenderComponent> m_RenderComponentes;

		explicit Scene(const std::string& name);

		std::string mName{};
		std::vector < std::shared_ptr<SceneObject>> mObjects{};

		static unsigned int idCounter; 
	};

}
