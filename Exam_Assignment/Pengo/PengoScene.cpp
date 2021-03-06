#include "pch.h"
#include "PengoScene.h"
#include "Components.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "Commands.h"
#include "States.h"
#include "InputManager.h"

namespace dae
{

	dae::PengoScene::PengoScene() : m_Grid{ nullptr }
	{
		//GRID
		m_Grid = new MoveGridManager(17, 13, 32);
		Add(m_Grid);

		//PLAYER
		GameObject* Player = new GameObject();

		//player animator
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
		
		//grid component player
		GridComponent* Gridcompon = new GridComponent();
		Gridcompon->AddTransform(Player->Transform());
		Gridcompon->Tag("Player");
		m_Grid->Connect(Gridcompon, 126);
		Player->AddComponent(Gridcompon);

		//input player
		InputComponent* inputcomp = new InputComponent(0, &InputManager::GetInstance());

		//move left
		Input* moveLeft = new Input;
		moveLeft->button = ControllerButton::DpadLeft;
		moveLeft->keyboard = 'A';
		MoveCommand* leftcom = new MoveCommand;
		leftcom->pengoDir = left;
		leftcom->gridcomp = Gridcompon;
		leftcom->animator = PlayerAnimator;
		moveLeft->pCommand = leftcom;
		inputcomp->AddInput(moveLeft);


		//move right
		Input* moveRight = new Input;
		moveRight->button = ControllerButton::DpadRight;
		moveRight->keyboard = 'D';
		MoveCommand* rightcom = new MoveCommand;
		rightcom->pengoDir = right;
		rightcom->gridcomp = Gridcompon;
		rightcom->animator = PlayerAnimator;
		moveRight->pCommand = rightcom;
		inputcomp->AddInput(moveRight);


		//move up
		Input* moveUp = new Input;
		moveUp->button = ControllerButton::DpadUp;
		moveUp->keyboard = 'W';
		MoveCommand* upcom = new MoveCommand;
		upcom->pengoDir = up;
		upcom->gridcomp = Gridcompon;
		upcom->animator = PlayerAnimator;
		moveUp->pCommand = upcom;
		inputcomp->AddInput(moveUp);

		//move left
		Input* moveDown = new Input;
		moveDown->button = ControllerButton::DpadDown;
		moveDown->keyboard = 'S';
		MoveCommand* downcom = new MoveCommand;
		downcom->pengoDir = down;
		downcom->gridcomp = Gridcompon;
		downcom->animator = PlayerAnimator;
		moveDown->pCommand = downcom;
		inputcomp->AddInput(moveDown);

		//interact 
		Input* interact = new Input;
		interact->button = ControllerButton::ButtonA;
		interact->keyboard = ' ';
		InteractCommand* interactcom = new InteractCommand;
		interactcom->gridcomp = Gridcompon;
		interactcom->animator = PlayerAnimator;
		interact->pCommand = interactcom;
		inputcomp->AddInput(interact);

		Player->AddComponent(inputcomp);

		//get player rendercomponent
		dae::RenderComponent* PlayerRender = GetSceneRenderer()->GetComponent(Player->Transform());
		PlayerRender->AttachAnimator(PlayerAnimator);

		//store and get texture
		dae::ResourceManager::GetInstance().StoreTexture("Pengo", dae::ResourceManager::GetInstance().LoadTexture("Pengos.jpg"));
		PlayerRender->Texture(dae::ResourceManager::GetInstance().GetTexture("Pengo"));

		//add plaer to scene
		Add(Player);
		

		//RESOURECES
		dae::ResourceManager::GetInstance().StoreTexture("Blocks", dae::ResourceManager::GetInstance().LoadTexture("Blocks.jpg"));
		dae::ResourceManager::GetInstance().StoreTexture("SnowBees", dae::ResourceManager::GetInstance().LoadTexture("SnowBees.jpg"));
		dae::ResourceManager::GetInstance().StoreTexture("Wall", dae::ResourceManager::GetInstance().LoadTexture("Wall.jpg"));

		//MAKES 4 WALLS AROUND THE BORDER 
		MakeWall();

		// 70 ICE BLOCKS
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

		// 3 DIAMOND BLOCKS
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
		// 4 SNOWBEES
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


	dae::PengoScene::~PengoScene()
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

	void PengoScene::MakeWall()
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
			m_Grid->Connect(Gridcomp, 17*13-(i+1));
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
			m_Grid->Connect(Gridcomp, 13 * (i+1));
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

