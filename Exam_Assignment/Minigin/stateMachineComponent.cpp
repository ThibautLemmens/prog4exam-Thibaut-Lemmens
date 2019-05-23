#include "MiniginPCH.h"
#include "stateMachineComponent.h"

dae::stateMachineComponent::stateMachineComponent(State * Entry)
{
	m_States.insert(std::pair<std::string, State*>(Entry->Name, Entry));
}

void dae::stateMachineComponent::AddState(State * state)
{
	std::unordered_map<std::string, State*>::iterator i = m_States.find(state->Name);
	if (i != m_States.end())
	{
		Logger::LogError(L"State Already Exists / name already in use");
	}
	else
	{
		m_States.insert(std::pair<std::string, State*>(state->Name, state));
	}
}

void dae::stateMachineComponent::Reset()
{
	m_CurrentState = (*m_States.begin()).second;
}

void dae::stateMachineComponent::Update()
{
	m_CurrentState->Update();
}

dae::State * dae::stateMachineComponent::GetState(std::string name)
{
	std::unordered_map<std::string, State*>::iterator i = m_States.find(name);
	if (i == m_States.end())
	{
		return nullptr;
		Logger::LogError(L"Command does not Exists");
	}
	else
	{
		return (*i).second;
	}
}

dae::State * dae::stateMachineComponent::GetActiveState()
{
	return m_CurrentState;
}

const std::string dae::stateMachineComponent::GetActiveState() const
{
	return m_CurrentState->Name;
}

void dae::stateMachineComponent::SetState(std::string name)
{
	m_CurrentState->End();
	std::unordered_map<std::string, State*>::iterator i = m_States.find(name);
	if (i == m_States.end())
	{
		Logger::LogError(L"state does not Exists");
		return;
	}
	else
	{
		m_CurrentState = (*i).second;
	}
	m_CurrentState->Entry();
}

void dae::stateMachineComponent::SetState(State * state)
{
	m_CurrentState->End();
	std::unordered_map<std::string, State*>::iterator i = m_States.find(state->Name);
	if (i == m_States.end())
	{
		Logger::LogError(L"state does not in StateMachine Component Exists");
		return;
	}
	else
	{
		m_CurrentState = (*i).second;
	}
	m_CurrentState->Entry();
}
