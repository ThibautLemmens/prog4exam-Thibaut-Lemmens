#pragma once
#include "BaseComponent.h"
#include "InputManager.h"

namespace dae
{
	struct Input
	{
		ControllerButton button;
		int keyboard;
		Command* pCommand;
	};

	class InputComponent final : public BaseComponent
	{
	public:
		virtual void Update() override;
		virtual void Initialize() override {};
		

		InputComponent(int player, InputManager* manager);
		~InputComponent();
		void AddInput(Input* input);
		void AddInput(ControllerButton button, int keyboard, Command* pCommand);
	private:
		InputManager* m_Manager;
		int m_Player;
		std::vector<Input*> m_Inputs;
	};
}
