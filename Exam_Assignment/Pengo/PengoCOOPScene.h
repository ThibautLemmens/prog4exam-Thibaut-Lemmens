#pragma once
#include "Scene.h"
#include "GridManager.h"


namespace dae
{
	class State;
	class PengoCOOPScene : public Scene
	{
	public:
		PengoCOOPScene();
		~PengoCOOPScene();
	private:
		GridManager* m_Grid;
		void MakeWall();
	};

}