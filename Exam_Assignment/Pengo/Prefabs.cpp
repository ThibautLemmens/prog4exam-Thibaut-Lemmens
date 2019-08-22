#include "pch.h"
#include "Prefabs.h"

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
	//delete Player;
	delete IceBlock;
	delete DiamondBlock;
	delete Wall;
	delete Enemy;
}

void dae::Prefabs::Init()
{
	Player = new GameObject;
	dae::AnimatorComponent* PlayerAnimator = new dae::AnimatorComponent(5,5);
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

	if (PlayerRender->Texture() == nullptr)
	{
		dae::Logger::LogInfo(L"nullptr tf???????");
	}
	
	dae::SceneManager::GetInstance().PresistendScene()->Add(Player);
	////Player->Transform()->Position(-10, -10, 10);

}
