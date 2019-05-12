#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"

void dae::SceneManager::Update()
{
	for(auto &scene : mScenes)
	{
		scene.Update();
	}
}

void dae::SceneManager::Render()
{
	for (auto& scene : mScenes)
	{
		scene.Render();
	}
}

dae::Scene* dae::SceneManager::CreateScene(const std::string& name)
{
	mScenes.push_back(Scene(name));
	return &mScenes.back();
}
