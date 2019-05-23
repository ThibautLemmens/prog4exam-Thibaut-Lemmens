#pragma once
#include "BaseComponent.h"
#include <unordered_map>
#include "AnimatorComponent.h"

namespace dae
{
	class State;
	class stateMachineComponent final : public BaseComponent
	{
	public:
		stateMachineComponent(State* Entry);
		~stateMachineComponent() = default;

		//Add state to StateMachine
		void AddState(State* state);

		//Attach animator for animation on entry of state
		void AttachAnimator(AnimatorComponent& animator) { if (m_HasAnimator) { Logger::LogInfo(L"Animator already attached -> reattaching Animator"); } m_HasAnimator = true; m_Animator = &animator; };
		void PlayAnimation() { if(m_CurrentState->AnimatorClipName.size() != 0 && m_HasAnimator) m_Animator->PlayClip(m_CurrentState->AnimatorClipName); };
		void PlayAnimation(std::string AnimationName) { if (m_HasAnimator) m_Animator->PlayClip(AnimationName); };

		//set statemachine to entry state
		void Reset();

		virtual void Initialize() override {};
		virtual void Update() override;

		//get name string or state*
		State* GetState(std::string name);

		//get string or state*
		State* GetActiveState();
		const std::string GetActiveState() const;

		//set state from the ones the statemchine holds
		void SetState(std::string name);
		void SetState(State* state);

	private:
		State* m_CurrentState;
		std::unordered_map<std::string, State*> m_States;

		bool m_HasAnimator;
		AnimatorComponent* m_Animator;
	};

	//remember to init the name in constructor when inheriting;
	class State
	{
	public:
		State(std::string name) { Name = name; };
		stateMachineComponent* StateMachine;
		std::string Name;
		std::string AnimatorClipName;
		//Advised to not call, only set
		virtual void Entry() { StateMachine->PlayAnimation(); };
		//Advised to not call, only set
		virtual void Update() {};
		//Advised to not call, only set
		virtual void End() {};

		const stateMachineComponent* const GetStateMachine() const { return StateMachine; };

	private:
		
	};

}