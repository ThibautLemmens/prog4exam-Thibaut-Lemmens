#include "MiniginPCH.h"
#include "PengoScene.h"
#include "Components.h"
#include "GameObject.h"

namespace dae
{

dae::PengoScene::PengoScene() : m_Grid{nullptr}
{
	m_Grid = new GridManager(15, 17);

	GameObject* Player = new GameObject();
	dae::AnimatorComponent* PlayerAnimator = new dae::AnimatorComponent(5, 5);
	PlayerAnimator->AddClip("RunDown", 0, 1, 0.24f);
	PlayerAnimator->AddClip("RunUp", 6, 7, 0.24f);
	PlayerAnimator->AddClip("RunSide", 11, 12, 0.24f);
	PlayerAnimator->AddClip("PushDown", 8, 8, 0.24f);
	PlayerAnimator->AddClip("PushUp", 21, 21, 0.24f);
	PlayerAnimator->AddClip("PushSide", 13, 14, 0.24f);
	PlayerAnimator->AddClip("Die", 4, 5, 0.24f);
	PlayerAnimator->PlayClip("RunDown");
	Player->AddComponent(PlayerAnimator);
	dae::RenderComponent* PlayerRender = dae::Renderer::GetInstance().GetComponent(Player->Transform());
	PlayerRender->AttachAnimator(PlayerAnimator);

	//Player->AddComponent(PlayerRender);
	dae::ResourceManager::GetInstance().StoreTexture("Pengo", dae::ResourceManager::GetInstance().LoadTexture("Pengos.jpg"));
	PlayerRender->Texture(dae::ResourceManager::GetInstance().GetTexture("Pengo"));
}


dae::PengoScene::~PengoScene()
{
}
}