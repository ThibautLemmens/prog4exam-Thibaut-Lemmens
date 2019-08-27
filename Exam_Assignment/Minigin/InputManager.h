#pragma once
#include <XInput.h>
#include "Singleton.h"
#include "Command.h"
#include <unordered_map>

namespace dae
{
	enum class ControllerButton
	{
		DpadUp = 0x0001,
		DpadDown = 0x0002,
		DpadLeft = 0x0004,
		DpadRight = 0x0008,
		Start = 0x0010,
		Back = 0x0020,
		LefthThumb = 0x0040,
		RightThumb = 0x0080,
		LefthShoulder = 0x0100,
		RightShoulder = 0x0200,
		ButtonA = 0x1000,
		ButtonB = 0x2000,
		ButtonX = 0x4000,
		ButtonY = 0x8000,
		NONE = 0x0000
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:

		virtual ~InputManager() override;
		void Init();
		bool ProcessInput();
		bool IsPressed(ControllerButton button,int player) const;
		bool IsPressed(int key, int player) const;
		Command* GetCommand(std::string name);
		void AddCommand(std::string name,Command* command);
	private:
		static const int MaxPlayers = 4;
		std::vector <XINPUT_STATE> currentState;
		BYTE *m_KeyboardState;
		std::unordered_map<std::string,Command*> m_Commands;
	};

}