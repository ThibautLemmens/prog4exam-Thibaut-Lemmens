#pragma once
#include "SceneObject.h"
#include "GridComponent.h"

namespace dae
{
	class GridManager final : public SceneObject
	{
	public:
		GridManager(int col, int row,int cellsize);
		~GridManager();

		//virtual void Initialize() override {};
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