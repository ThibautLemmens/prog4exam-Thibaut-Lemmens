#include "pch.h"
#include "Prefabs.h"
#include "Components.h"
#include "ResourceManager.h"

dae::Prefabs::Prefabs()
	: Player{ nullptr }
	, IceBlock{ nullptr }
	, DiamondBlock{ nullptr }
	, Wall{ nullptr }
	, Enemy{ nullptr }
{

}


dae::Prefabs::~Prefabs()
{
}

void dae::Prefabs::Init()
{
	Player = new GameObject;
	dae::AnimatorComponent* PlayerAnimator = new dae::AnimatorComponent(5,5);
	PlayerAnimator->AddClip("runDown", 0, 1, 0.12f);
	PlayerAnimator->AddClip("RunUp", 6, 7, 0.12f);
	PlayerAnimator->AddClip("RunSide", 11, 12, 0.12f);
	PlayerAnimator->AddClip("PushDown", 8, 8, 0.12f);
	PlayerAnimator->AddClip("PushUp", 21, 21, 0.12f);
	PlayerAnimator->AddClip("PushSide", 13, 14, 0.12f);
	PlayerAnimator->AddClip("Die", 4, 5, 0.12f);
	dae::RenderComponent* PlayerRender = dae::Renderer::GetInstance().GetComponent(Player->Transform());
	PlayerRender->AttachAnimator(PlayerAnimator);
	PlayerRender->Texture(dae::ResourceManager::GetInstance().LoadTexture())
}
