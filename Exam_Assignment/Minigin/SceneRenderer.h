#pragma once
#include "RenderComponent.h"

class Scene;
namespace dae
{
	class SceneRenderer
	{
	public:
		SceneRenderer();
		~SceneRenderer();

		void RenderUpdate();
		void Render();

		RenderComponent* GetComponent(TransformComponent* transform);
		bool RemoveComponent(RenderComponent* rendercomponent);
	private:
		std::vector<RenderComponent*> m_RenderComponentes;
		Scene* m_Scene;
	};

}