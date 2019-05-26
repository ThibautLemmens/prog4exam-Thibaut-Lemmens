#include "MiniginPCH.h"
#include "Logger.h"
#include "InputManager.h"
#include <SDL.h>


bool dae::InputManager::ProcessInput()
{
	ZeroMemory(&currentState, sizeof(XINPUT_STATE));
	XInputGetState(0, &currentState);

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

bool dae::InputManager::IsPressed(ControllerButton button) const
{
	return (currentState.Gamepad.wButtons & static_cast<WORD>(button)) != 0;
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
