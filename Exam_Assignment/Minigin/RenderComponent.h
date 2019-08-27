#pragma once
#include "BaseComponent.h"
#include "AnimatorComponent.h"
#include "TransformComponent.h"
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#include "glm/vec2.hpp"
#include "glm/vec4.hpp"
#pragma warning(pop)
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

		void RenderUpdate();
		void Render() const;

		void AttachAnimator(AnimatorComponent* animator) { if (m_HasAnimator) { Logger::LogInfo(L"Animator already attached -> reattaching Animator"); } m_HasAnimator = true; m_Animator = animator; };

		//set Texture
		void Texture(dae::Texture2D* texture) { m_Texture = texture; };
		//get Texture
		dae::Texture2D* const Texture() const { return m_Texture; };

		void SetDimensions(Rect dest, Rect source) { m_Source = source; m_Dest = dest; m_HasSource = true; m_HasDest = true; };

		void Source(Rect source) { m_Source = source; m_HasSource = true; };
		Rect Source() const { return m_Source; };

		void Destination(Rect dest) { m_Dest = dest; m_HasDest = true; };
		Rect Destination() const { return m_Dest; };

		void Offset(glm::vec2 offset) { m_Offset = offset; };
		glm::vec2 Offset() const { return m_Offset; };

		SDL_Rect Convert(Rect info) const;
		
		TransformComponent* Transform() const { return m_Transform; };

	private:
		bool m_HasSource = false;
		Rect m_Source;

		bool m_HasDest = false;
		Rect m_Dest;

		glm::vec2 m_Offset = {0,0};

		dae::Texture2D* m_Texture = nullptr;

		//Option to have animator
		bool m_HasAnimator = false;
		AnimatorComponent* m_Animator = nullptr;
		TransformComponent* m_Transform = nullptr;
	};

}
