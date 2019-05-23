#pragma once
#include "BaseComponent.h"
#include "InputManager.h"

namespace dae
{
	class InputComponent final : public BaseComponent
	{
	public:
		InputComponent();
		~InputComponent();
		//get Command from InputManager
		void AddCommand(std::string command);
	private:
		std::unordered_map<std::string,Command*> m_pCommands;
	};
}
