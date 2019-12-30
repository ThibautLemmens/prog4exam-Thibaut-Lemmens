#include "MiniginPCH.h"
#include "PixelGrid.h"
#include "Renderer.h"
#include "Texture2D.h"

pixSim::PixelGrid::PixelGrid()
{
	mTexture = SDL_CreateTexture(dae::Renderer::GetInstance().GetSDLRenderer(), SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, celSize, celSize);
}


pixSim::PixelGrid::~PixelGrid()
{
	SDL_DestroyTexture(mTexture);
//	delete mTexture;
}

void pixSim::PixelGrid::Update()
{
	if (shouldUpdated){

	}
}

void pixSim::PixelGrid::Render()
{
	
}

void pixSim::PixelGrid::AddPixel(UpdateReturn pixel)
{
}
