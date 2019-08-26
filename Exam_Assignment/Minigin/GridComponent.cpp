#include "MiniginPCH.h"
#include "GridComponent.h"
#include "GridManager.h"
#include <cmath>

dae::GridComponent::GridComponent()
{
}


dae::GridComponent::~GridComponent()
{
	Transform = nullptr;
	Grid = nullptr;
}

void dae::GridComponent::Update()
{
	if (IsMoving())
	{
		Time += 1 / MoveSpeed * Time::GetInstance().DeltaTime();
		if (Time > 1)
		{
			Transform->Position(DestinationVector.x, DestinationVector.y);
		}
		else
		{
			glm::vec2 pos = Lerp(startVector, DestinationVector, Time);
			Transform->Position(pos.x, pos.y);
		}
		
	}
}

void dae::GridComponent::MoveTo(int pos)
{
	int x = (pos % Grid->GetCol()) * Grid->GetSize();
	int y = (pos / (Grid->GetCol() + 1)) * Grid->GetSize();

	Transform->Position((float)x, (float)y);
}

int dae::GridComponent::GetPos() const
{
	return GridPos;
}

int dae::GridComponent::GetDest() const
{
	return Destination;
}

bool dae::GridComponent::IsTrigger() const
{
	return trigger;
}

bool dae::GridComponent::IsMoving() const
{
	return Move;
}

void dae::GridComponent::SetSpeed(float speed)
{
	MoveSpeed = speed;
}

float dae::GridComponent::GetSpeed()
{
	return MoveSpeed;
}
