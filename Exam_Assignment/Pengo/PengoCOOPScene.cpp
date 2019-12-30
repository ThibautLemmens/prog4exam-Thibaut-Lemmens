#include "pch.h"
#include "PengoCOOPScene.h"
#include "Components.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "Commands.h"
#include "States.h"
#include "InputManager.h"

namespace dae
{

	dae::PengoCOOPScene::PengoCOOPScene() : m_Grid{ nullptr }
	{
		m_Grid = new MoveGridManager(17, 13, 32);
		Add(m_Grid);


		GameObject* Player = new GameObject();
		dae::AnimatorComponent* PlayerAnimator = new dae::AnimatorComponent(5, 5);
		PlayerAnimator->AddClip("RunDown", 0, 1, 0.24f);
		PlayerAnimator->AddClip("RunUp", 5, 6, 0.24f);
		PlayerAnimator->AddClip("RunRight", 10, 11, 0.24f);
		PlayerAnimator->AddClip("Runleft", 23, 24, 0.24f);
		PlayerAnimator->AddClip("PushDown", 21, 22, 0.24f);
		PlayerAnimator->AddClip("PushUp", 19, 20, 0.24f);
		PlayerAnimator->AddClip("PushLeft", 12, 13, 0.24f);
		PlayerAnimator->AddClip("PushRight", 15, 16, 0.24f);
		PlayerAnimator->AddClip("Die", 4, 5, 0.24f);
		PlayerAnimator->PlayClip("RunDown");
		Player->AddComponent(PlayerAnimator);

		GridComponent* Gridcompon = new GridComponent();
		Gridcompon->AddTransform(Player->Transform());
		Gridcompon->Tag("Player");
		m_Grid->Connect(Gridcompon, 126);
		Player->AddComponent(Gridcompon);

		InputComponent* inputcomp = new InputComponent(0, &InputManager::GetInstance());

		Input* moveLeft = new Input;
		moveLeft->button = ControllerButton::DpadLeft;
		moveLeft->keyboard = 'A';
		MoveCommand* leftcom = new MoveCommand;
		leftcom->pengoDir = left;
		leftcom->gridcomp = Gridcompon;
		leftcom->animator = PlayerAnimator;
		moveLeft->pCommand = leftcom;
		inputcomp->AddInput(moveLeft);

		Input* moveRight = new Input;
		moveRight->button = ControllerButton::DpadRight;
		moveRight->keyboard = 'D';
		MoveCommand* rightcom = new MoveCommand;
		rightcom->pengoDir = right;
		rightcom->gridcomp = Gridcompon;
		rightcom->animator = PlayerAnimator;
		moveRight->pCommand = rightcom;
		inputcomp->AddInput(moveRight);

		Input* moveUp = new Input;
		moveUp->button = ControllerButton::DpadUp;
		moveUp->keyboard = 'W';
		MoveCommand* upcom = new MoveCommand;
		upcom->pengoDir = up;
		upcom->gridcomp = Gridcompon;
		upcom->animator = PlayerAnimator;
		moveUp->pCommand = upcom;
		inputcomp->AddInput(moveUp);

		Input* moveDown = new Input;
		moveDown->button = ControllerButton::DpadDown;
		moveDown->keyboard = 'S';
		MoveCommand* downcom = new MoveCommand;
		downcom->pengoDir = down;
		downcom->gridcomp = Gridcompon;
		downcom->animator = PlayerAnimator;
		moveDown->pCommand = downcom;
		inputcomp->AddInput(moveDown);

		Input* interact = new Input;
		interact->button = ControllerButton::ButtonA;
		interact->keyboard = ' ';
		InteractCommand* interactcom = new InteractCommand;
		interactcom->gridcomp = Gridcompon;
		interactcom->animator = PlayerAnimator;
		interact->pCommand = interactcom;
		inputcomp->AddInput(interact);

		Player->AddComponent(inputcomp);

		dae::RenderComponent* PlayerRender = GetSceneRenderer()->GetComponent(Player->Transform());
		PlayerRender->AttachAnimator(PlayerAnimator);

		dae::ResourceManager::GetInstance().StoreTexture("Pengo", dae::ResourceManager::GetInstance().LoadTexture("Pengos.jpg"));
		PlayerRender->Texture(dae::ResourceManager::GetInstance().GetTexture("Pengo"));
		Add(Player);

		GameObject* Player2 = new GameObject();
		dae::AnimatorComponent* PlayerAnimator2 = new dae::AnimatorComponent(5, 5);
		PlayerAnimator2->AddClip("RunDown", 0, 1, 0.24f);
		PlayerAnimator2->AddClip("RunUp", 5, 6, 0.24f);
		PlayerAnimator2->AddClip("RunRight", 10, 11, 0.24f);
		PlayerAnimator2->AddClip("Runleft", 23, 24, 0.24f);
		PlayerAnimator2->AddClip("PushDown", 21, 22, 0.24f);
		PlayerAnimator2->AddClip("PushUp", 19, 20, 0.24f);
		PlayerAnimator2->AddClip("PushLeft", 12, 13, 0.24f);
		PlayerAnimator2->AddClip("PushRight", 15, 16, 0.24f);
		PlayerAnimator2->AddClip("Die", 4, 5, 0.24f);
		PlayerAnimator2->PlayClip("RunDown");
		Player2->AddComponent(PlayerAnimator2);

		GridComponent* Gridcompon2 = new GridComponent();
		Gridcompon2->AddTransform(Player2->Transform());
		Gridcompon2->Tag("Player");
		m_Grid->Connect(Gridcompon2, 118);
		Player2->AddComponent(Gridcompon2);

		InputComponent* inputcomp2 = new InputComponent(1, &InputManager::GetInstance());

		Input* moveLeft2 = new Input;
		moveLeft2->button = ControllerButton::DpadLeft;
		moveLeft2->keyboard = 'J';
		MoveCommand* leftcom2 = new MoveCommand;
		leftcom2->pengoDir = left;
		leftcom2->gridcomp = Gridcompon2;
		leftcom2->animator = PlayerAnimator2;
		moveLeft2->pCommand = leftcom2;
		inputcomp2->AddInput(moveLeft2);

		Input* moveRight2 = new Input;
		moveRight2->button = ControllerButton::DpadRight;
		moveRight2->keyboard = 'L';
		MoveCommand* rightcom2 = new MoveCommand;
		rightcom2->pengoDir = right;
		rightcom2->gridcomp = Gridcompon2;
		rightcom2->animator = PlayerAnimator2;
		moveRight2->pCommand = rightcom2;
		inputcomp2->AddInput(moveRight2);

		Input* moveUp2 = new Input;
		moveUp2->button = ControllerButton::DpadUp;
		moveUp2->keyboard = 'I';
		MoveCommand* upcom2 = new MoveCommand;
		upcom2->pengoDir = up;
		upcom2->gridcomp = Gridcompon2;
		upcom2->animator = PlayerAnimator2;
		moveUp2->pCommand = upcom2;
		inputcomp2->AddInput(moveUp2);

		Input* moveDown2 = new Input;
		moveDown2->button = ControllerButton::DpadDown;
		moveDown2->keyboard = 'K';
		MoveCommand* downcom2 = new MoveCommand;
		downcom2->pengoDir = down;
		downcom2->gridcomp = Gridcompon2;
		downcom2->animator = PlayerAnimator2;
		moveDown2->pCommand = downcom2;
		inputcomp2->AddInput(moveDown2);

		Input* interact2 = new Input;
		interact2->button = ControllerButton::ButtonA;
		interact2->keyboard = 'P';
		InteractCommand* interactcom2 = new InteractCommand;
		interactcom2->gridcomp = Gridcompon2;
		interactcom2->animator = PlayerAnimator2;
		interact2->pCommand = interactcom2;
		inputcomp2->AddInput(interact2);

		Player2->AddComponent(inputcomp2);

		dae::RenderComponent* PlayerRender2 = GetSceneRenderer()->GetComponent(Player2->Transform());
		PlayerRender2->AttachAnimator(PlayerAnimator2);

		PlayerRender2->Texture(dae::ResourceManager::GetInstance().GetTexture("Pengo"));
		Add(Player2);

		dae::ResourceManager::GetInstance().StoreTexture("Blocks", dae::ResourceManager::GetInstance().LoadTexture("Blocks.jpg"));
		dae::ResourceManager::GetInstance().StoreTexture("SnowBees", dae::ResourceManager::GetInstance().LoadTexture("SnowBees.jpg"));
		dae::ResourceManager::GetInstance().StoreTexture("Wall", dae::ResourceManager::GetInstance().LoadTexture("Wall.jpg"));

		MakeWall();

		//std::vector<GameObject*>Blocks;
		for (size_t i = 0; i < 70; i++)
		{
			GameObject* block = new GameObject();
			dae::AnimatorComponent* BlockAnim = new dae::AnimatorComponent(3, 5);
			BlockAnim->AddClip("Block", 0, 0, 20.24f);
			BlockAnim->AddClip("Destroy", 1, 8, 0.12f);
			BlockAnim->PlayClip("Block");
			block->AddComponent(BlockAnim);
			dae::RenderComponent* BlockRender = GetSceneRenderer()->GetComponent(block->Transform());
			BlockRender->Texture(dae::ResourceManager::GetInstance().GetTexture("Blocks"));
			BlockRender->AttachAnimator(BlockAnim);
			/*block->AddComponent(BlockRender);*/
			GridComponent* Gridcomp = new GridComponent();
			Gridcomp->Tag("Block");
			bool add = true;
			Gridcomp->AddTransform(block->Transform());
			while (add)
			{
				add = m_Grid->Connect(Gridcomp, rand() % (13 * 17));
				add = !add;
			}
			block->AddComponent(Gridcomp);
			BlockNormal* normal = new BlockNormal;
			normal->gridcomp = Gridcomp;
			BlockDestroy* Destroy = new BlockDestroy;
			Destroy->gridcomp = Gridcomp;
			Destroy->anim = BlockAnim;
			BlockGlide* Glide = new BlockGlide;
			Glide->gridcomp = Gridcomp;

			stateMachineComponent* statemach = new stateMachineComponent(normal, "Normal");
			statemach->AddState(Destroy, "Destroy");
			statemach->AddState(Glide, "Glide");
			statemach->SetState("Normal");
			block->AddComponent(statemach);

			Add(block);
		}
		for (size_t i = 0; i < 3; i++)
		{
			GameObject* block = new GameObject();
			dae::AnimatorComponent* DiaBlockAnim = new dae::AnimatorComponent(3, 5);
			DiaBlockAnim->AddClip("Normal", 11, 12, 0.24f);
			DiaBlockAnim->AddClip("Bonus", 11, 14, 0.12f);
			DiaBlockAnim->PlayClip("Normal");
			block->AddComponent(DiaBlockAnim);
			dae::RenderComponent* BlockRender = GetSceneRenderer()->GetComponent(block->Transform());
			BlockRender->Texture(dae::ResourceManager::GetInstance().GetTexture("Blocks"));
			BlockRender->AttachAnimator(DiaBlockAnim);
			/*block->AddComponent(BlockRender);*/
			GridComponent* Gridcomp = new GridComponent();
			Gridcomp->Tag("DBlock");
			bool add = true;
			Gridcomp->AddTransform(block->Transform());
			while (add)
			{
				add = m_Grid->Connect(Gridcomp, rand() % (13 * 17));
				add = !add;
			}
			block->AddComponent(Gridcomp);
			Add(block);
		}

		for (size_t i = 0; i < 4; i++)
		{
			GameObject* Enemy = new GameObject();
			dae::AnimatorComponent* EnemyAnim = new dae::AnimatorComponent(6, 5);
			EnemyAnim->AddClip("Spawn", 0, 5, 0.24f);
			EnemyAnim->AddClip("Stun", 6, 6, 0.12f);
			EnemyAnim->AddClip("down", 7, 8, 0.12f);
			EnemyAnim->AddClip("left", 9, 10, 0.12f);
			EnemyAnim->AddClip("right", 28, 29, 0.12f);
			EnemyAnim->AddClip("up", 11, 12, 0.12f);
			EnemyAnim->AddClip("downAttack", 13, 14, 0.12f);
			EnemyAnim->AddClip("leftAttack", 15, 16, 0.12f);
			EnemyAnim->AddClip("rightAttack", 15, 16, 0.12f);
			EnemyAnim->AddClip("upAttack", 17, 18, 0.12f);
			EnemyAnim->AddClip("flatUp", 19, 20, 0.12f);
			EnemyAnim->AddClip("flatleft", 21, 22, 0.12f);
			EnemyAnim->AddClip("flatRight", 21, 22, 0.12f);
			EnemyAnim->AddClip("flatDown", 23, 24, 0.12f);
			EnemyAnim->PlayClip("Spawn");
			Enemy->AddComponent(EnemyAnim);
			dae::RenderComponent* BlockRender = GetSceneRenderer()->GetComponent(Enemy->Transform());
			BlockRender->Texture(dae::ResourceManager::GetInstance().GetTexture("SnowBees"));
			BlockRender->AttachAnimator(EnemyAnim);
			/*block->AddComponent(BlockRender);*/
			GridComponent* Gridcomp = new GridComponent();
			Gridcomp->Tag("Enemy");
			Gridcomp->SetTrigger(true);
			bool add = true;
			Gridcomp->AddTransform(Enemy->Transform());
			while (add)
			{
				add = m_Grid->Connect(Gridcomp, rand() % (13 * 17));
				add = !add;
			}
			Enemy->AddComponent(Gridcomp);

			EnemySpawn* spawn = new EnemySpawn;
			spawn->anim = EnemyAnim;
			spawn->gridcomp = Gridcomp;
			EnemyWander* wander = new EnemyWander;
			wander->anim = EnemyAnim;
			wander->gridcomp = Gridcomp;
			stateMachineComponent* statemach = new stateMachineComponent(spawn, "Spawn");
			statemach->AddState(wander, "Wander");
			statemach->SetState("Spawn");
			Enemy->AddComponent(statemach);

			Add(Enemy);
		}


	}


	dae::PengoCOOPScene::~PengoCOOPScene()
	{
		delete m_Grid;
		delete mSceneRenderer;
		/*	for (auto gameObject : deleteVec)
			{
				delete gameObject;
			}*/
		for (size_t i = 0; i < mObjects.size(); i++)
		{
			delete mObjects[i];
		}
	}
	void PengoCOOPScene::MakeWall()
	{
		GameObject* Upwall = new GameObject();
		dae::AnimatorComponent* WallAnimUp = new dae::AnimatorComponent(1, 6);
		WallAnimUp->AddClip("normal", 0, 1, 1.28f);
		WallAnimUp->AddClip("wave", 2, 5, 0.12f);
		WallAnimUp->PlayClip("normal");
		Upwall->AddComponent(WallAnimUp);
		for (int i = 0; i < 13; i++)
		{
			dae::RenderComponent* BlockRender = GetSceneRenderer()->GetComponent(Upwall->Transform());
			BlockRender->Texture(dae::ResourceManager::GetInstance().GetTexture("Wall"));
			BlockRender->AttachAnimator(WallAnimUp);
			BlockRender->Offset({ i * 32,0 });
			GridComponent* Gridcomp = new GridComponent();
			Gridcomp->Tag("Wall");
			TransformComponent* transform = new TransformComponent();
			Upwall->AddComponent(transform);
			Gridcomp->AddTransform(transform);
			m_Grid->Connect(Gridcomp, i);
			Upwall->AddComponent(Gridcomp);
		}
		Add(Upwall);

		GameObject* Downwall = new GameObject();
		dae::AnimatorComponent* WallAnimDown = new dae::AnimatorComponent(1, 6);
		WallAnimDown->AddClip("normal", 0, 1, 1.28f);
		WallAnimDown->AddClip("wave", 2, 5, 0.12f);
		WallAnimDown->PlayClip("normal");
		Downwall->AddComponent(WallAnimDown);
		for (int i = 0; i < 13; i++)
		{
			TransformComponent* transform = new TransformComponent();
			dae::RenderComponent* BlockRender = GetSceneRenderer()->GetComponent(transform);
			BlockRender->Texture(dae::ResourceManager::GetInstance().GetTexture("Wall"));
			BlockRender->AttachAnimator(WallAnimDown);
			//BlockRender->Offset({ i * -32,0 });
			GridComponent* Gridcomp = new GridComponent();
			Gridcomp->Tag("Wall");
			Downwall->AddComponent(transform);
			Gridcomp->AddTransform(transform);
			m_Grid->Connect(Gridcomp, 17 * 13 - (i + 1));
			Downwall->AddComponent(Gridcomp);
		}
		Add(Downwall);

		GameObject* Leftwall = new GameObject();
		dae::AnimatorComponent* WallAnimLeft = new dae::AnimatorComponent(1, 6);
		WallAnimLeft->AddClip("normal", 0, 1, 1.28f);
		WallAnimLeft->AddClip("wave", 2, 5, 0.12f);
		WallAnimLeft->PlayClip("normal");
		Leftwall->AddComponent(WallAnimLeft);
		for (int i = 0; i < 15; i++)
		{
			TransformComponent* transform = new TransformComponent();
			dae::RenderComponent* BlockRender = GetSceneRenderer()->GetComponent(transform);
			BlockRender->Texture(dae::ResourceManager::GetInstance().GetTexture("Wall"));
			BlockRender->AttachAnimator(WallAnimLeft);
			//BlockRender->Offset({ i * -32,0 });
			GridComponent* Gridcomp = new GridComponent();
			Gridcomp->Tag("Wall");
			Leftwall->AddComponent(transform);
			Gridcomp->AddTransform(transform);
			m_Grid->Connect(Gridcomp, 13 * (i + 1));
			Leftwall->AddComponent(Gridcomp);
		}
		Add(Leftwall);


		GameObject* RightWall = new GameObject();
		dae::AnimatorComponent* WallAnimRight = new dae::AnimatorComponent(1, 6);
		WallAnimRight->AddClip("normal", 0, 1, 1.28f);
		WallAnimRight->AddClip("wave", 2, 5, 0.12f);
		WallAnimRight->PlayClip("normal");
		RightWall->AddComponent(WallAnimRight);
		for (int i = 0; i < 15; i++)
		{
			TransformComponent* transform = new TransformComponent();
			dae::RenderComponent* BlockRender = GetSceneRenderer()->GetComponent(transform);
			BlockRender->Texture(dae::ResourceManager::GetInstance().GetTexture("Wall"));
			BlockRender->AttachAnimator(WallAnimRight);
			//BlockRender->Offset({ i * -32,0 });
			GridComponent* Gridcomp = new GridComponent();
			Gridcomp->Tag("Wall");
			RightWall->AddComponent(transform);
			Gridcomp->AddTransform(transform);
			m_Grid->Connect(Gridcomp, 13 * (i + 1) + 12);
			RightWall->AddComponent(Gridcomp);
		}
		Add(RightWall);
	}
}

