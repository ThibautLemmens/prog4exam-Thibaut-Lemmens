#pragma once
#include "SDL.h"
#include "PixelSimulation.h"

namespace pixSim
{
	class PixelGrid
	{
		static const unsigned int celSize = 128;
	public:
		PixelGrid();
		~PixelGrid();

		void Update();
		void Render();

		void AddPixel(UpdateReturn pixel);

		bool shouldUpdated;
		bool shouldRender;

	private:
		SDL_Texture* mTexture;
		unsigned int mType[celSize];
	};
}
