#pragma once
#include "BaseComponent.h"
#include "AnimatorComponent.h"
#include "TransformComponent.h"
#include "glm\common.hpp"
#include "Texture2D.h"

struct SDL_Rect;

namespace dae
{
	struct Rect
	{
		int x, y, length, height;
	};

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

		//set Texture
		void Texture(std::shared_ptr<dae::Texture2D> texture) { m_Texture = texture; };
		//get Texture
		std::shared_ptr<dae::Texture2D> const Texture() const { return m_Texture; };

		void SetDimensions(Rect dest, Rect source) { m_Source = source; m_Dest = dest; m_HasSource = true; m_HasDest = true; };

		void Source(Rect source) { m_Source = source; m_HasSource = true; };
		Rect Source() const { return m_Source; };

		void Destination(Rect dest) { m_Dest = dest; m_HasDest = true; };
		Rect Destination() const { return m_Dest; };

		SDL_Rect Convert(Rect info) const;
		
	private:
		bool m_HasSource = false;
		Rect m_Source;

		bool m_HasDest = false;
		Rect m_Dest;

		std::shared_ptr<dae::Texture2D> m_Texture = nullptr;

		//Option to have animator
		bool m_HasAnimator = false;
		AnimatorComponent* m_Animator = nullptr;
		TransformComponent* m_Transform = nullptr;
	};

}
