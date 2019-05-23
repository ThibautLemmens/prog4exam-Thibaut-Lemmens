#pragma once
#include <XInput.h>
#include "Singleton.h"
#include "Command.h"
#include <unordered_map>

namespace dae
{
	enum class ControllerButton
	{
		ButtonA,
		ButtonB,
		ButtonX,
		ButtonY,
		ButtonRT,
		ButtonLT
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();
		bool IsPressed(ControllerButton button) const;
		Command* GetCommand(std::string name);
		void AddCommand(std::string name,Command* command);
	private:
		XINPUT_STATE currentState{};
		std::unordered_map<std::string,Command*> m_Commands;
	};

}