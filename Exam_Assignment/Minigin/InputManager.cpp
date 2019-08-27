#include "MiniginPCH.h"
#include "InputManager.h"
#include <SDL.h>


dae::InputManager::~InputManager()
{
	delete m_KeyboardState;
}

void dae::InputManager::Init()
{
	m_KeyboardState = new BYTE[256];
	GetKeyboardState(m_KeyboardState);


	for (int i{ 0 }; i < MaxPlayers; ++i)
	{
		XINPUT_STATE state;
		currentState.push_back(state);
	}
}

bool dae::InputManager::ProcessInput()
{
	//ZeroMemory(&currentState, sizeof(XINPUT_STATE));
	for (unsigned int i{ 0 }; i < currentState.size(); ++i)
	{
		XInputGetState(i, &currentState[i]);

	}

	GetKeyboardState(m_KeyboardState);

	

	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) { 
			return false;
		}
		if (e.type == SDL_KEYDOWN) {
			
		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {
			
		}
	}

	return true;
}

bool dae::InputManager::IsPressed(ControllerButton button, int player) const
{
	return (currentState[player].Gamepad.wButtons & static_cast<WORD>(button)) != 0;
}

bool dae::InputManager::IsPressed(int key, int player) const
{
	if(GetAsyncKeyState(key)) return true;
	return false;
}

dae::Command* dae::InputManager::GetCommand(std::string name)
{
	std::unordered_map<std::string, Command*>::iterator i = m_Commands.find(name);
	if (i == m_Commands.end())
	{
		return nullptr;
		Logger::LogError(L"Command does not Exists");
	}
	else
	{
		return (*i).second;
	}
}

void dae::InputManager::AddCommand(std::string name, Command * command)
{
	std::unordered_map<std::string, Command*>::iterator i = m_Commands.find(name);
	if (i != m_Commands.end())
	{
		Logger::LogError(L"Command Already Exists");
	}
	else
	{
		m_Commands.insert(std::pair<std::string, Command*>(name, command));
	}
}
