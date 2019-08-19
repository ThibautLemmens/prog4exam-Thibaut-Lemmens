#pragma once
#include "Command.h"
using namespace dae;
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

class EnterCommand	 final : public Command
{
public:
	virtual void Execute() override;
};