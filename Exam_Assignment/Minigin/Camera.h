#pragma once
#include <SDL_Rect.h>
#include "TransformComponent.h"

#define originalSize 512

namespace dae
{
	class Camera
	{
	public:
		Camera();
		~Camera();

		//easy to zoom feature
		void Size(const float &size);
		float Size();

		//return orthographic view frustum
		SDL_Rect const GetView() const;

		TransformComponent* GetTransform();

	private:
		SDL_Rect View{ 0,0,originalSize,originalSize };
		float Sizeview = 1;
		TransformComponent* transform;
	};
}