#include "MiniginPCH.h"
#include "Camera.h"


dae::Camera::Camera()
{
	transform = new TransformComponent();
}


dae::Camera::~Camera()
{
}

void dae::Camera::Size(const float &size)
{
	Sizeview = size;
	View = { (int)transform->Position().x,(int)transform->Position().y,int(originalSize*Sizeview),int(originalSize*Sizeview) };
}

float dae::Camera::Size()
{
	return Sizeview;
}

SDL_Rect const dae::Camera::GetView() const
{
	return View;
}

dae::TransformComponent * dae::Camera::GetTransform()
{
	return transform;
}
