#include "MiniginPCH.h"
#include "stateMachineComponent.h"

dae::stateMachineComponent::stateMachineComponent(State * Entry)
{
}

void dae::stateMachineComponent::Reset()
{
}

void dae::stateMachineComponent::Update()
{
}

dae::State * dae::stateMachineComponent::GetState(std::string name)
{
	return nullptr;
}

const std::string dae::stateMachineComponent::GetState(std::string name) const
{
	return std::string();
}

dae::State * dae::stateMachineComponent::GetActiveState()
{
	return nullptr;
}

const std::string dae::stateMachineComponent::GetActiveState() const
{
	return std::string();
}
