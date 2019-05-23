#include "MiniginPCH.h"
#include "InputComponent.h"


dae::InputComponent::InputComponent()
{
}


dae::InputComponent::~InputComponent()
{
}

void dae::InputComponent::AddCommand(std::string command)
{
	m_pCommands.insert(std::pair<std::string,Command*>(command,dae::InputManager::GetInstance().GetCommand(command)));
}
