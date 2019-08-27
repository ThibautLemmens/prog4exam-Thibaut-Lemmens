#include "MiniginPCH.h"
#include "stateMachineComponent.h"

dae::stateMachineComponent::stateMachineComponent(State * Entry, std::string name)
{
	Entry->StateMachine = this;
	m_States.insert(std::pair<std::string, State*>(name, Entry));
	m_CurrentName = name;
	m_CurrentState = Entry;
}

dae::stateMachineComponent::~stateMachineComponent()
{
	//std::unordered_map<std::string, State*>::iterator it = m_States.begin();

	//// Iterate over the map using iterator
	//while (it != m_States.end())
	//{
	//	delete it->second;
	//	it++;
	//}
	for (auto st:  m_States)
	{
		delete st.second;
	}
};

void dae::stateMachineComponent::AddState(State * state, std::string name)
{
	std::unordered_map<std::string, State*>::iterator i = m_States.find(name);
	if (i != m_States.end())
	{
		Logger::LogError(L"State Already Exists / name already in use");
	}
	else
	{
		state->StateMachine = this;
		m_States.insert(std::pair<std::string, State*>(name, state));
	}
}

void dae::stateMachineComponent::Reset()
{
	m_CurrentName = (*m_States.begin()).first;
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
		Logger::LogError(L"Command does not Exists");
		return nullptr;
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

const std::string dae::stateMachineComponent::GetActiveStateName() const
{
	return m_CurrentName;
}

void dae::stateMachineComponent::SetState(std::string name)
{
	if(m_CurrentState != nullptr ) m_CurrentState->End();
	std::unordered_map<std::string, State*>::iterator i = m_States.find(name);
	if (i == m_States.end())
	{
		Logger::LogError(L"state does not Exists");
		return;
	}
	else
	{
		m_CurrentName = (*i).first;
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
		m_CurrentName = (*i).first;
		m_CurrentState = (*i).second;
	}
	m_CurrentState->Entry();
}
