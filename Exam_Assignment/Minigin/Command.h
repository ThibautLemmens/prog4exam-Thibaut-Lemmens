#pragma once
#include <iostream>
namespace dae
{
	class InputComponent;
	class Command
	{
	public:
		virtual ~Command() = default;
		virtual void Execute() = 0;
		InputComponent* m_Input;
	};
}