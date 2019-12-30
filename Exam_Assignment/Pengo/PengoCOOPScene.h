#pragma once
#include "Scene.h"
#include "MoveGridManager.h"


namespace dae
{
	class State;
	class PengoCOOPScene : public Scene
	{
	public:
		PengoCOOPScene();
		~PengoCOOPScene();
	private:
		MoveGridManager* m_Grid;
		void MakeWall();
	};

}