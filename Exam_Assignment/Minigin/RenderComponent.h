#pragma once
#include "BaseComponent.h"
#include "AnimatorComponent.h"
#include "TransformComponent.h"
#include "glm\common.hpp"
#include "Texture2D.h"
#include "Renderer.h"

struct SDL_Rect;
namespace dae
{
	class RenderComponent final : public BaseComponent
	{

	public:
		RenderComponent(TransformComponent* transform) :m_Transform{ transform } {};
		virtual ~RenderComponent() {};

		RenderComponent(const RenderComponent& other) { m_Animator = other.m_Animator; m_HasAnimator = other.m_HasAnimator; m_Animator = other.m_Animator; m_Transform = other.m_Transform; };
		RenderComponent(RenderComponent&& other) noexcept = delete;
		RenderComponent& operator=(const RenderComponent& other) = delete;
		RenderComponent& operator=(RenderComponent&& other) { m_Animator = other.m_Animator; m_HasAnimator = other.m_HasAnimator; m_Animator = other.m_Animator; m_Transform = other.m_Transform;};

		void Render() const
		{
			if (m_HasAnimator)
			{
				//dest
				SDL_Rect *dest = new SDL_Rect;
				dest->x = static_cast<int>(m_Transform->Position().x);
				dest->y = static_cast<int>(m_Transform->Position().y);

				SDL_QueryTexture(m_Texture->GetSDLTexture(), nullptr, nullptr, &dest->w, &dest->h);

				dest->w *= (int)m_Transform->Scale().x;
				dest->h *= (int)m_Transform->Scale().y;

				//source
				SDL_Rect *src = new SDL_Rect(m_Animator->GetSource(dest->w, dest->h));
				
				Renderer::GetInstance().RenderTexture(*m_Texture, dest, src);
				return;
			}
			Renderer::GetInstance().RenderTexture(*m_Texture, m_Transform->Position().x, m_Transform->Position().y);
		
		};

		void AttachAnimator(AnimatorComponent& animator) { if (m_HasAnimator) { Logger::LogError(L"Animator already attached"); } m_HasAnimator = true; m_Animator = &animator; };

	private:
		Texture2D* m_Texture = nullptr;

		//Option to have animator
		bool m_HasAnimator = false;
		AnimatorComponent* m_Animator = nullptr;
		TransformComponent* m_Transform = nullptr;
	};

}
