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
#include "RenderingStack.h"

struct SDL_Rect;

namespace dae
{
	//Placeholder for SDL_Rect
	struct Rect
	{
		int x, y, width, height;
	};

	class RenderComponent final : public BaseComponent
	{

	public:
		//Init with <Transform>
		RenderComponent(TransformComponent* Transform) { m_Transform = Transform; };
		virtual ~RenderComponent() {};

		//init
		virtual void Initialize() override {};
		//Update
		virtual void Update() override {};

		//Rule of 5
		RenderComponent(const RenderComponent& other) :m_Animator{ other.m_Animator }, m_HasAnimator{ other.m_HasAnimator }, m_Transform{ other.m_Transform } {};
		RenderComponent(RenderComponent&& other) noexcept :m_Animator{ other.m_Animator }, m_HasAnimator{ other.m_HasAnimator }, m_Transform{ other.m_Transform } {};
		RenderComponent& operator=(const RenderComponent& other) { return *this = RenderComponent(other); };
		RenderComponent& operator=(RenderComponent&& other) noexcept { m_Animator = other.m_Animator; m_HasAnimator = other.m_HasAnimator; m_Transform = other.m_Transform; return *this; };

		////RenderUpdate
		//void RenderUpdate();
		//Update
		dae::RenderData Render();

		//Set <Animator component>
		void AttachAnimator(AnimatorComponent* animator) { if (m_HasAnimator) { Logger::LogInfo(L"Animator already attached -> reattaching Animator"); } m_HasAnimator = true; m_Animator = animator; };

		//set Texture
		void Texture(dae::Texture2D* texture) { m_Texture = texture; };
		//get Texture
		dae::Texture2D* const Texture() const { return m_Texture; };

		//set <source> and <destination> Rectangle 
		void SetDimensions(Rect dest, Rect source) { m_Source = source; m_Dest = dest; m_HasSource = true; m_HasDest = true; };

		//set <source rectangle>
		void Source(Rect source) { m_Source = source; m_HasSource = true; };
		//get source rectangle
		Rect Source() const { return m_Source; };

		//set <destination rectangle?
		void Destination(Rect dest) { m_Dest = dest; m_HasDest = true; };
		//get destination rectangle
		Rect Destination() const { return m_Dest; };

		//set <offset>
		void Offset(glm::vec2 offset) { m_Offset = offset; };
		//get offset
		glm::vec2 Offset() const { return m_Offset; };

		//Give SDL_Rect from Rect
		SDL_Rect Convert(Rect info) const;
		
		//get transform
		TransformComponent* Transform() const { return m_Transform; };

	private:
		//Is source rectangle givin? if no, calculate using Texture data.
		bool m_HasSource = false;
		Rect m_Source;
		//Is destination rectangle givin? if no, calculate using Texture data and transform.
		bool m_HasDest = false;
		Rect m_Dest;
		//Offset
		glm::vec2 m_Offset = {0,0};
		//Texure
		dae::Texture2D* m_Texture = nullptr;
		//Is Animator attached? if no, calculate normal. if yes, get source rectangle from animator
		bool m_HasAnimator = false;
		AnimatorComponent* m_Animator = nullptr;
		TransformComponent* m_Transform = nullptr;
	};

}
