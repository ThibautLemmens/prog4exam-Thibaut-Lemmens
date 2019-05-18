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

dae::Scene* dae::SceneManager::CreateScene(const std::string& name)
{
	mScenes.push_back(new Scene(name));
	return mScenes.back();
}
