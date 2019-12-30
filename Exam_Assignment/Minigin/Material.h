#pragma once
#include "Texture2D.h"

struct ShaderResources
{
	SDL_Texture* BaseColor;
};

struct Reflective :  ShaderResources
{
	SDL_Texture* BaseColor;
	SDL_Texture* Reflection;
	SDL_Texture* RenderTarget;
};

class Material
{
public:
	Material();
	virtual ~Material();
	virtual void Update()=0;
};

class StaticMaterial : public Material
{
public:
	StaticMaterial();
	virtual ~StaticMaterial();
	virtual void Update();
private:
};

class DynamicMaterial : public Material
{
public:
	DynamicMaterial();
	virtual ~DynamicMaterial();
	virtual void Update();
private:

};
