#pragma once
#include "SceneObject.h"
#include "GridComponent.h"

namespace dae
{
	class MoveGridManager final : public SceneObject
	{
	public:
		//Init Grid, give <collums>, <rows> and <size of each cell>
		MoveGridManager(int col, int row,int cellsize);
		~MoveGridManager();

		//Update
		virtual void Update() override {};


		std::vector<GridComponent*> GetLocation(int location);
		bool Connect(GridComponent* component, int location);
		void Disconnect(GridComponent* component);

		int GetCol() { return m_Cols; };
		int GetRow() { return m_Rows; };
		int GetSize() { return m_CellSize; };

	private:
		int m_Cols, m_Rows, m_CellSize;
		std::vector<GridComponent*> m_ReturnVector;
		std::vector<GridComponent*> m_Grid;
	};
}