#pragma once
#include "Scene.h"
#include "MoveGridManager.h"


namespace dae
{
	class State;
	class PengoScene : public Scene
	{
	public:
		PengoScene();
		~PengoScene();
	private:
		MoveGridManager* m_Grid;
		void MakeWall();
	};

}