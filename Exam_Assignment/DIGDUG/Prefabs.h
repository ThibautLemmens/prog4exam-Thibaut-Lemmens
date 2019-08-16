#pragma once
#include "GameObject.h"

namespace dae
{
	class Prefabs
	{
	public:
		Prefabs();
		~Prefabs();

	private:
		GameObject* Player;
		GameObject* IceBlock;
		GameObject* DiamondBlock;
		GameObject* Wall;
		GameObject* Enemy;
	};
}

