#pragma once
#include "Scene.h"
#include "GridManager.h"
namespace dae
{
	class PengoScene : public Scene
	{
	public:
		PengoScene();
		~PengoScene();
	private:
		GridManager* m_Grid;
	};

}