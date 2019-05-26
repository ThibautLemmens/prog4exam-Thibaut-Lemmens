#pragma once
#include "Singleton.h"
#include "RenderComponent.h"
struct SDL_Window;
struct SDL_Renderer;
struct SDL_Rect;
namespace dae
{
	class Texture2D;
	class TransformComponent;
	class Renderer final : public Singleton<Renderer>
	{
		SDL_Renderer* mRenderer = nullptr;

	public:
		void Init(SDL_Window* window);
		void Render();
		void Destroy();

		void RenderTexture(const Texture2D& texture, float x, float y) const;
		void RenderTexture(const Texture2D& texture, float x, float y, SDL_Rect* src) const;
		void RenderTexture(const Texture2D& texture, float x, float y, float width, float height) const;
		void RenderTexture(const Texture2D& texture, const SDL_Rect* dst, const SDL_Rect* src) const;
		void RenderTexture(const Texture2D& texture, const SDL_Rect* dst) const;

		SDL_Renderer* GetSDLRenderer() const { return mRenderer; };

		RenderComponent* GetComponent(TransformComponent* transform);

		bool Sort(const RenderComponent& rc1,const RenderComponent& rc2);

	private:
		std::vector<RenderComponent> m_RenderComponentes;

	};
}

