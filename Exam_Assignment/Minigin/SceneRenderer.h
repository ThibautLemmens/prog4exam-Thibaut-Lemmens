#pragma once
#include "RenderComponent.h"


namespace dae
{
	class SceneRenderer
	{
	public:
		SceneRenderer();
		~SceneRenderer();
	private:
		std::vector<RenderComponent*> m_RenderComponentes;
	};

}