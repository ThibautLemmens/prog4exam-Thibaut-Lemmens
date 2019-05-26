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
	Command* com{ dae::InputManager::GetInstance().GetCommand(command) };
	com->m_Input = this;
	m_pCommands.insert(std::pair<std::string,Command*>(command, com));
}

void dae::InputComponent::RemoveCommand(std::string command)
{
	std::unordered_map<std::string, Command*>::iterator i = m_pCommands.find(command);
	if (i == m_pCommands.end())
	{
		Logger::LogError(L"Commands does not Exists");
	}
	else
	{
		m_pCommands.erase(command);
	}
}
