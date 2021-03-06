#include "MiniginPCH.h"
#include "Renderer.h"
#include <SDL.h>
#include <glew.h>
#include <gl\GL.h>
#include "RenderComponent.h"
#include "Texture2D.h"
#include "SceneManager.h"
#include <iostream>
#include <fstream>

void dae::Renderer::Init(SDL_Window * window)
{
	mRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
	if (mRenderer == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}
}

void dae::Renderer::Render()
{
	SDL_RenderClear(mRenderer);

	SceneManager::GetInstance().Render();
	
	SDL_RenderPresent(mRenderer);
}

void dae::Renderer::Destroy()
{
	if (mRenderer != nullptr)
	{
		SDL_DestroyRenderer(mRenderer);
		mRenderer = nullptr;
	}
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y) const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void dae::Renderer::RenderTexture(const Texture2D & texture, float x, float y, SDL_Rect* src) const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), src, &dst);
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const float width, const float height) const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(width);
	dst.h = static_cast<int>(height);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void dae::Renderer::RenderTexture(const Texture2D& texture,const SDL_Rect* dst , const SDL_Rect* src) const
{
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), src, dst);
}

void dae::Renderer::RenderTexture(const Texture2D & texture,const SDL_Rect* dst) const
{
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, dst);
}
