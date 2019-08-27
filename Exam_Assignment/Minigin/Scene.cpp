#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"

unsigned int dae::Scene::idCounter = 0;

dae::Scene::~Scene()
{
	delete mSceneRenderer;
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
		if(gameObject != nullptr) gameObject->Update();
	}
}


