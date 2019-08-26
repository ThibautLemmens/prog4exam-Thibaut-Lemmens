#include "MiniginPCH.h"
#include "AnimatorComponent.h"
#include <SDL.h>


SDL_Rect dae::AnimatorComponent::GetSource(const int& width, const int& Height)
{
	int srcHeight, srcWidth;

	srcHeight = Height / m_Cols;
	srcWidth = width / m_Rows;

	SDL_Rect src;
	src.x = (m_CurrentFrame % m_Rows) * srcWidth;
	src.y = (m_CurrentFrame / (m_Rows)) * srcHeight;
	src.w = srcWidth;
	src.h = srcHeight;
	return src;
};
