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

void dae::SceneManager::RenderUpdate()
{
	for (auto &scene : mScenes)
	{
		scene->GetSceneRenderer()->RenderUpdate();
	}
}

void dae::SceneManager::Render()
{
	for (auto &scene : mScenes)
	{
		scene->GetSceneRenderer()->Render();
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
	mScenes.push_back(new Scene);
	mScenes.back()->mName = name;
	return mScenes.back();
}

void dae::SceneManager::AddScene(Scene * scene)
{
	mScenes.push_back(scene);
}
