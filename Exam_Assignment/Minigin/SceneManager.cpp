#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"

void dae::SceneManager::Update()
{
	for(auto &scene : mScenes)
	{
		scene->Update();
	}
}

dae::SceneManager::~SceneManager()
{
	for (Scene* scene : mScenes)
	{
		delete scene;
	}
}

dae::Scene* dae::SceneManager::CreateScene(const std::string& name)
{
	mScenes.push_back(new Scene(name));
	return mScenes.back();
}
