#include "MiniginPCH.h"
#include "RenderComponent.h"
#include "Texture2D.h"
#include "Renderer.h"
#include <SDL.h>

void dae::RenderComponent::Render() const
{
	if (m_Texture == nullptr) { return; }
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
	if (m_HasDest)
	{
		if (m_HasSource)
		{
			Renderer::GetInstance().RenderTexture(*m_Texture, &Convert(m_Dest), &Convert(m_Source));
			return;
		}
		Renderer::GetInstance().RenderTexture(*m_Texture, &Convert(m_Dest));
		return;
	}
	Renderer::GetInstance().RenderTexture(*m_Texture, m_Transform->Position().x, m_Transform->Position().y);

}

SDL_Rect dae::RenderComponent::Convert(Rect info) const
{
	SDL_Rect a;
	a.x = info.x;
	a.y = info.y;
	a.w = info.length;
	a.h = info.height;

	return a;
}
