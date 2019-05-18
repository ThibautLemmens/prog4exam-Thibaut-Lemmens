#pragma once
#include "BaseComponent.h"
#include "AnimatorComponent.h"
#include "TransformComponent.h"
#include "glm\common.hpp"
#include "Texture2D.h"

struct SDL_Rect;
namespace dae
{
	class RenderComponent final : public BaseComponent
	{

	public:
		RenderComponent(TransformComponent* transform) :m_Transform{ transform } {};
		virtual ~RenderComponent() {};

		RenderComponent(const RenderComponent& other) :m_Animator{ other.m_Animator }, m_HasAnimator{ other.m_HasAnimator }, m_Transform{ other.m_Transform } {};
		RenderComponent(RenderComponent&& other) noexcept :m_Animator{ other.m_Animator }, m_HasAnimator{ other.m_HasAnimator }, m_Transform{ other.m_Transform } {};
		RenderComponent& operator=(const RenderComponent& other) { return *this = RenderComponent(other); };
		RenderComponent& operator=(RenderComponent&& other) noexcept { m_Animator = other.m_Animator; m_HasAnimator = other.m_HasAnimator; m_Transform = other.m_Transform; return *this; };

		void Render() const;

		void AttachAnimator(AnimatorComponent& animator) { if (m_HasAnimator) { Logger::LogWarning(L"Animator already attached, reattached"); } m_HasAnimator = true; m_Animator = &animator; };

	private:
		Texture2D* m_Texture = nullptr;

		//Option to have animator
		bool m_HasAnimator = false;
		AnimatorComponent* m_Animator = nullptr;
		TransformComponent* m_Transform = nullptr;
	};

}
