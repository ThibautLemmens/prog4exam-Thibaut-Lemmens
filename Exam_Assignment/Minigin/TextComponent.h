#pragma once
#include "BaseComponent.h"
#include "AnimatorComponent.h"
#include "TransformComponent.h"
#include "glm\common.hpp"
#include "Texture2D.h"
#include "Font.h"
#include "Renderer.h"

namespace dae
{
	class TextComponent final : public BaseComponent
	{

	public:
		TextComponent(TransformComponent* transform) :m_Transform{ transform } {};
		virtual ~TextComponent() {};

		TextComponent(const TextComponent& other) {m_Transform = other.m_Transform; };
		TextComponent(TextComponent&& other) noexcept = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) noexcept = delete;

		void Render() 
		{
			if (m_NeedsUpdate)
			{
				const SDL_Color color = { 255,255,255 }; // only white text is supported now
				const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), color);
				if (surf == nullptr)
				{
					throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
				}
				auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
				if (texture == nullptr)
				{
					throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
				}
				SDL_FreeSurface(surf);
				m_Texture = std::make_shared<Texture2D>(texture);
			}
		};

		glm_vec4 Color()const {return m_Color;};


	private:
		glm_vec4 m_Color = {255,255,255,255};
		TransformComponent* m_Transform = nullptr;
		bool m_NeedsUpdate;
		std::string m_Text;
		std::shared_ptr<Font> m_Font;
		std::shared_ptr<Texture2D> m_Texture;
	};

}
