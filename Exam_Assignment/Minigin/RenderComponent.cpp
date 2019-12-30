#include "MiniginPCH.h"
#include "RenderComponent.h"
#include "Texture2D.h"
#include "Renderer.h"
#include <SDL.h>

dae::RenderData dae::RenderComponent::Render()
{
	if (m_Texture == nullptr)
	{
		dae::Logger::LogError(L"RenderComponent has no texture");
		return RenderData(nullptr,SDL_Rect(),SDL_Rect());
	}
	if (m_Transform == nullptr)
	{ 
		dae::Logger::LogError(L"RenderComponent has no transform");
		return RenderData(nullptr, SDL_Rect(), SDL_Rect());
	}
	if (m_HasAnimator)
	{
		//dest
		SDL_Rect dest;
		dest.x = static_cast<int>(m_Transform->Position().x + m_Offset.x);
		dest.y = static_cast<int>(m_Transform->Position().y + m_Offset.y);

		SDL_QueryTexture(m_Texture->GetSDLTexture(), nullptr, nullptr, &dest.w, &dest.h);

		SDL_Rect ImageSize = dest;

		dest.w /= m_Animator->Rows();
		dest.h /= m_Animator->Cols();
	

		//source
		SDL_Rect src(m_Animator->GetSource(ImageSize.w, ImageSize.h));

		src.w *= (int)m_Transform->Scale().x;
		src.h *= (int)m_Transform->Scale().y;

		//Renderer::GetInstance().RenderTexture(*m_Texture, &dest, &src);


		return RenderData(m_Texture,dest,src);
	}
	if (m_HasDest)
	{
		if (m_HasSource)
		{
			//Renderer::GetInstance().RenderTexture(*m_Texture, &Convert(m_Dest), &Convert(m_Source));
			return RenderData(m_Texture, Convert(m_Dest), Convert(m_Source));
		}
		//Renderer::GetInstance().RenderTexture(*m_Texture, &Convert(m_Dest));
		SDL_Rect src(m_Animator->GetSource(m_Dest.width, m_Dest.height));
		src.w *= (int)m_Transform->Scale().x;
		src.h *= (int)m_Transform->Scale().y;
		return RenderData(m_Texture, Convert(m_Dest), src);
	}
	//Renderer::GetInstance().RenderTexture(*m_Texture, m_Transform->Position().x, m_Transform->Position().y);
	//dest
	SDL_Rect dest;
	dest.x = static_cast<int>(m_Transform->Position().x + m_Offset.x);
	dest.y = static_cast<int>(m_Transform->Position().y + m_Offset.y);
	SDL_QueryTexture(m_Texture->GetSDLTexture(), nullptr, nullptr, &dest.w, &dest.h);

	SDL_Rect src(m_Animator->GetSource(dest.w, dest.h));
	src.w *= (int)m_Transform->Scale().x;
	src.h *= (int)m_Transform->Scale().y;
	return RenderData(m_Texture, dest, src);
}

SDL_Rect dae::RenderComponent::Convert(Rect info) const
{
	SDL_Rect a;
	a.x = info.x;
	a.y = info.y;
	a.w = info.width;
	a.h = info.height;

	return a;
}
