#pragma once
struct SDL_Texture;

namespace dae
{
	class Texture2D
	{
	public:
		SDL_Texture* GetSDLTexture() const;
		explicit Texture2D(SDL_Texture* texture);
		~Texture2D();

		Texture2D(const Texture2D &other) { mTexture = other.mTexture; };
		Texture2D(Texture2D &&other) { mTexture = other.mTexture; };
		Texture2D & operator= (const Texture2D & other) { mTexture = other.mTexture; };
		Texture2D & operator= (const Texture2D &&other) { mTexture = other.mTexture; };
	private:
		SDL_Texture* mTexture;
	};
}
