#include "MiniginPCH.h"
#include "InputComponent.h"


void dae::InputComponent::Update()
{
	for (size_t i = 0; i < m_Inputs.size(); i++)
	{
		if (m_Manager->IsPressed(m_Inputs[i]->button,m_Player)|| m_Manager->IsPressed(m_Inputs[i]->keyboard, m_Player))
		{
			m_Inputs[i]->pCommand->Execute();
		}
	}
}

dae::InputComponent::InputComponent(int player, InputManager* manager)
	:m_Player{player},m_Manager{manager}

{
}


dae::InputComponent::~InputComponent()
{
	for (Input* in: m_Inputs)
	{
		delete in->pCommand;
		delete in;
	}
}

void dae::InputComponent::AddInput(Input * input)
{
	m_Inputs.push_back(input);
}

void dae::InputComponent::AddInput(ControllerButton button, int keyboard, Command * pCommand)
{
	Input* input = new Input;
	input->button = button;
	input->pCommand = pCommand;
	input->keyboard = keyboard;
	m_Inputs.push_back(input);
}

