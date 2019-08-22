#pragma once
#include "Singleton.h"
#include "GridComponent.h"

namespace dae
{
	class GridManager final
	{
	public:
		GridManager(int col, int row);
		~GridManager();

		GridComponent* GetLocation(int location);
		void Connect(GridComponent* component, int location);
		void Disconnect(int location);
		void Disconnect(GridComponent* component);
	private:
		int m_Cols, m_Rows;
		std::vector<GridComponent*> m_Grid;
	};
}
