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
		RenderComponent(TransformComponent* Transform) { m_Transform = Transform; };
		virtual ~RenderComponent() {};

		virtual void Initialize() override {};
		virtual void Update() override {};

		RenderComponent(const RenderComponent& other) :m_Animator{ other.m_Animator }, m_HasAnimator{ other.m_HasAnimator }, m_Transform{ other.m_Transform } {};
		RenderComponent(RenderComponent&& other) noexcept :m_Animator{ other.m_Animator }, m_HasAnimator{ other.m_HasAnimator }, m_Transform{ other.m_Transform } {};
		RenderComponent& operator=(const RenderComponent& other) { return *this = RenderComponent(other); };
		RenderComponent& operator=(RenderComponent&& other) noexcept { m_Animator = other.m_Animator; m_HasAnimator = other.m_HasAnimator; m_Transform = other.m_Transform; return *this; };

		void Render() const;

		void AttachAnimator(AnimatorComponent* animator) { if (m_HasAnimator) { Logger::LogInfo(L"Animator already attached -> reattaching Animator"); } m_HasAnimator = true; m_Animator = animator; };

		void Texture(Texture2D* texture) { m_Texture = texture; };
		Texture2D* const Texture() const { return m_Texture; };

		void SetDimensions(SDL_Rect dest, SDL_Rect source) { m_Source = source; m_Dest = dest; m_HasSource = true; m_HasDest = true; };

		void Source(SDL_Rect source) { m_Source = source; m_HasSource = true; };
		SDL_Rect Source() const { return m_Source; };

		void Destination(SDL_Rect dest) { m_Dest = dest; m_HasDest = true; };
		SDL_Rect Destination() const { return m_Dest; };

	private:
		bool m_HasSource = false;
		SDL_Rect m_Source;

		bool m_HasDest = false;
		SDL_Rect m_Dest;

		Texture2D* m_Texture = nullptr;

		//Option to have animator
		bool m_HasAnimator = false;
		AnimatorComponent* m_Animator = nullptr;
		TransformComponent* m_Transform = nullptr;
	};

}
