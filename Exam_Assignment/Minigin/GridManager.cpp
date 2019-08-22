#include "MiniginPCH.h"
#include "GridManager.h"

dae::GridManager::GridManager(int col, int row)
{
}

dae::GridManager::~GridManager()
{
	m_Grid.erase(m_Grid.begin(),m_Grid.end());
}
