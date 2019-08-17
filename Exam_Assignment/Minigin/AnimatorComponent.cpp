#include "MiniginPCH.h"
#include "AnimatorComponent.h"
#include <SDL.h>


SDL_Rect dae::AnimatorComponent::GetSource(const int& width, const int& Height)
{
	int srcHeight, srcWidth;

	srcHeight = Height / m_Cols;
	srcWidth = width / m_Rows;

	SDL_Rect src;
	src.x = (m_CurrentFrame % m_Cols) * srcWidth;
	src.y = (m_CurrentFrame / (m_Cols + 1)) * srcHeight;
	src.w = srcWidth;
	src.h = srcHeight;
	return src;
};
