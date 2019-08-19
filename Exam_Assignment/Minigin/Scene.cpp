#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"

unsigned int dae::Scene::idCounter = 0;

dae::Scene::Scene(const std::string& name) : mName(name) {}

dae::Scene::~Scene()
{
	for (auto gameObject : mObjects)
	{
		delete gameObject;
	}
}

void dae::Scene::Add(SceneObject* object)
{
	mObjects.push_back(object);
}

void dae::Scene::Update()
{
	for(auto gameObject : mObjects)
	{
		gameObject->Update();
	}
}


