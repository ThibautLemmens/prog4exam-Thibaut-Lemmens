#include "MiniginPCH.h"
#include "MoveGridManager.h"

dae::MoveGridManager::MoveGridManager(int col, int row, int cellsize)
	:m_Cols{col},
	m_Rows{row},
	m_CellSize{cellsize}
{
	m_ReturnVector.resize(4);
}

dae::MoveGridManager::~MoveGridManager()
{
}

std::vector<dae::GridComponent*>  dae::MoveGridManager::GetLocation(int location)
{
	m_ReturnVector.clear();
	for (size_t i = 0; i < m_Grid.size(); i++)
	{
		if (m_Grid[i]->GetPos() == location)
		{
			m_ReturnVector.push_back(m_Grid[i]);
			continue;
		}
		if (m_Grid[i]->IsMoving())
		{
			if (m_Grid[i]->GetDest() == location)
			{
				m_ReturnVector.push_back(m_Grid[i]);
			}
		}
	}
	return m_ReturnVector;
}

bool dae::MoveGridManager::Connect(GridComponent * component, int location)
{
	for (GridComponent* c : m_Grid)
	{
		if (c->GetPos() == location)
		{
			return false;
		}
	}
	m_Grid.push_back(component);
	component->AddManager(this);
	component->MoveTo(location);
	return true;
}

void dae::MoveGridManager::Disconnect(GridComponent * component)
{
	for (size_t i = 0; i < m_Grid.size(); i++)
	{
		if (m_Grid[i] == component)
		{
			std::swap(m_Grid[i], m_Grid.back());
			m_Grid.pop_back();
		}
	}
}
