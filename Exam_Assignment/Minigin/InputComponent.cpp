#include "MiniginPCH.h"
#include "InputComponent.h"


void dae::InputComponent::Update()
{
}

dae::InputComponent::InputComponent(int player)
	:m_Player{player}

{
}


dae::InputComponent::~InputComponent()
{
	for (Input* in: m_Inputs)
	{
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

