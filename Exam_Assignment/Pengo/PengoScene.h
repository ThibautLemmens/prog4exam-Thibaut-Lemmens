#pragma once
#include "Scene.h"
#include "GridManager.h"


namespace dae
{
	class State;
	class PengoScene : public Scene
	{
	public:
		PengoScene();
		~PengoScene();
	private:
		GridManager* m_Grid;
		void MakeWall();
	};

}