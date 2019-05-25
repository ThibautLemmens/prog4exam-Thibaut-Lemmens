#pragma once
#include "Command.h"

//player
class PumpCommand final : public Command
{
public:
	virtual void Execute() override;
};

//player and enemy
class MoveCommand final : public Command
{
public:
	virtual void Execute() override;
	float Speed;
};

class Move final : public Command
{
public:
	virtual void Execute() override;
};