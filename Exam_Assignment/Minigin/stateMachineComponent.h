#pragma once
#include "BaseComponent.h"
#include <unordered_map>
#include "AnimatorComponent.h"

namespace dae
{
	typedef void(*EntryFunction)();
	typedef void(*UpdateFunction)();
	typedef void(*EndFunction)();

	struct State
	{


		std::string Name;
		std::string AnimatorClipName;
		stateMachineComponent* StateMachine;

		//Advised to not call, only set
		EntryFunction Entry;
		//Advised to not call, only set
		UpdateFunction Update;
		//Advised to not call, only set
		EndFunction End;
	};

	class stateMachineComponent final : public BaseComponent
	{
	public:
		stateMachineComponent(State* Entry);
		~stateMachineComponent() = default;

		//Attach animator for animation on entry of state
		void AttachAnimator(AnimatorComponent& animator) { if (m_HasAnimator) { Logger::LogInfo(L"Animator already attached -> reattaching Animator"); } m_HasAnimator = true; m_Animator = &animator; };

		//set statemachine to entry state
		void Reset();

		virtual void Initialize() override {};
		virtual void Update() override;

		//get string or state*
		State* GetState(std::string name);
		const std::string GetState(std::string name) const;

		//get string or state*
		State* GetActiveState();
		const std::string GetActiveState() const;

	private:
		State* m_CurrentState;
		std::unordered_map<std::string, State*> m_States;

		bool m_HasAnimator;
		AnimatorComponent* m_Animator;
	};

}