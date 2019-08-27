#pragma once
#include "components.h"
#include "Components.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "Command.h"
#include "GridManager.h"
#include "structs.h"

namespace dae
{
	class BlockGlide final : public dae::State
	{
	public:
		BlockGlide() = default;
		virtual ~BlockGlide()  override {};
		std::string Name = "Glide";
		std::string AnimatorClipName = "Destroy";
		Direction dir = up;
		dae::GridComponent* gridcomp;
		virtual void Entry() override
		{
			auto a = gridcomp->GetManager()->GetLocation(gridcomp->GetPos() - 13);
			if (a.size() > 0)
			{
				if (a[0]->Tag() == "Player") dir = down;
			}
			a = gridcomp->GetManager()->GetLocation(gridcomp->GetPos() + 13);
			if (a.size() > 0)
			{
				if (a[0]->Tag() == "Player") dir = up;
			}
			a = gridcomp->GetManager()->GetLocation(gridcomp->GetPos() - 1);
			if (a.size() > 0)
			{
				if (a[0]->Tag() == "Player") dir = right;
			}
			a = gridcomp->GetManager()->GetLocation(gridcomp->GetPos() + 1);
			if (a.size() > 0)
			{
				if (a[0]->Tag() == "Player") dir = left;
			}


			int gotoPos = 0;
			switch (dir)
			{
			case up:
				gotoPos = gridcomp->GetPos() - 13;
				break;
			case down:
				gotoPos = gridcomp->GetPos() + 13;
				break;
			case left:
				gotoPos = gridcomp->GetPos() - 1;
				break;
			case right:
				gotoPos = gridcomp->GetPos() + 1;
				break;
			default:
				break;
			}

			auto comp = gridcomp->GetManager()->GetLocation(gotoPos);
			if (comp.size() != 0)
			{
				for (size_t i = 0; i < comp.size(); i++)
				{
					if (comp[i]->Tag() == "Wall")
					{
						stateMachineComponent* x = gridcomp->GetGameObject()->GetComponent<stateMachineComponent>();
						if (x != nullptr) x->SetState("Destroy");
					}
					if (comp[i]->Tag() == "Block")
					{
						stateMachineComponent* x = gridcomp->GetGameObject()->GetComponent<stateMachineComponent>();
						if (x != nullptr) x->SetState("Destroy");
					}
					if (comp[i]->Tag() == "DBlock")
					{
						stateMachineComponent* x = gridcomp->GetGameObject()->GetComponent<stateMachineComponent>();
						if (x != nullptr) x->SetState("Destroy");
					}
					if (comp[i]->Tag() == "Enemy")
					{
						stateMachineComponent* x = gridcomp->GetGameObject()->GetComponent<stateMachineComponent>();
						if (x != nullptr) x->SetState("Destroy");
					}
				}
			}
		};
		//Advised to not call, only set
		virtual void Update() override
		{
			if (gridcomp->IsMoving() == false)
			{

				int gotoPos = 0;
				switch (dir)
				{
				case up:
					gotoPos = gridcomp->GetPos() - 13;
					break;
				case down:
					gotoPos = gridcomp->GetPos() + 13;
					break;
				case left:
					gotoPos = gridcomp->GetPos() - 1;
					break;
				case right:
					gotoPos = gridcomp->GetPos() + 1;
					break;
				default:
					break;
				}

				auto comp = gridcomp->GetManager()->GetLocation(gotoPos);
				if (comp.size() == 0)
				{

					gridcomp->SetMoving(true);
					gridcomp->SetDest(gridcomp->GridLocation(gotoPos));
					gridcomp->SetDestLocation(gotoPos);
				}
				if (comp.size() != 0)
				{
					for (size_t i = 0; i < comp.size(); i++)
					{
						if (comp[i]->Tag() == "Enemy")
						{
							stateMachineComponent* x = comp[i]->GetGameObject()->GetComponent<stateMachineComponent>();
							if (x != nullptr) x->SetState("Die");
						}
						else
						{
							if (comp[i]->Tag() == "Block")
							{
								stateMachineComponent* x = gridcomp->GetGameObject()->GetComponent<stateMachineComponent>();
								if (x != nullptr) x->SetState("Normal");
							}
						}
					}
				}
			}
		};
		//Advised to not call, only set
		virtual void End()  override {};

	private:

	};

	class BlockNormal final : public dae::State
	{
	public:
		BlockNormal() = default;
		virtual ~BlockNormal()  override {};
		std::string Name = "Normal";
		std::string AnimatorClipName = "Destroy";
		Direction dir = up;
		dae::GridComponent* gridcomp;
		virtual void Entry() override
		{
		};
		//Advised to not call, only set
		virtual void Update() override
		{
		};
		//Advised to not call, only set
		virtual void End()  override {};

	private:

	};

	class BlockDestroy final : public dae::State
	{
	public:
		BlockDestroy() = default;
		virtual ~BlockDestroy() override {};
		std::string Name = "Destroy";
		std::string AnimatorClipName = "Destroy";
		Direction dir = up;
		dae::GridComponent* gridcomp;
		dae::AnimatorComponent* anim;
		float time;
		virtual void Entry() override
		{
			anim->PlayClip(AnimatorClipName);
		};
		//Advised to not call, only set
		virtual void Update() override
		{
			time += Time::GetInstance().DeltaTime();
			if (time > (anim->CurrentClip().EndFrame - anim->CurrentClip().StartFrame)*anim->CurrentClip().TickRate)
			{
				gridcomp->MoveTo(gridcomp->GetPos() + 1000 + rand()%100);
			}
		};
		//Advised to not call, only set
		virtual void End()  override {};

	private:

	};

	class EnemyWander final : public dae::State
	{
	public:
		EnemyWander() = default;
		virtual ~EnemyWander() override {};
		std::string Name = "Wander";
		std::string AnimatorClipName = "Destroy";
		Direction dir = up;
		dae::GridComponent* gridcomp;
		dae::AnimatorComponent* anim;
		virtual void Entry() override
		{
			gridcomp->SetSpeed(0.48f);
		};
		//Advised to not call, only set
		virtual void Update() override
		{
			if (gridcomp->IsMoving() == false)
			{

				int random = rand() % 4;
				switch (random)
				{
				case 0:
					dir = up;
					break;
				case 1:
					dir = down;
					break;
				case 2:
					dir = right;
					break;
				case 3:
					dir = left;
					break;
				default:
					break;
				}

				int gotoPos=0;
				switch (dir)
				{
				case up:
					gotoPos = gridcomp->GetPos() - 13;
					break;
				case down:
					gotoPos = gridcomp->GetPos() + 13;
					break;
				case left:
					gotoPos = gridcomp->GetPos() - 1;
					break;
				case right:
					gotoPos = gridcomp->GetPos() + 1;
					break;
				default:
					break;
				}

				auto comp = gridcomp->GetManager()->GetLocation(gotoPos);
				if (comp.size() == 0)
				{

					switch (dir)
					{
					case up:
						anim->PlayClip("up");
						break;
					case down:
						anim->PlayClip("down");
						break;
					case left:
						anim->PlayClip("left");
						break;
					case right:
						anim->PlayClip("right");
						break;
					default:
						break;
					}

					gridcomp->SetMoving(true);
					gridcomp->SetDest(gridcomp->GridLocation(gotoPos));
					gridcomp->SetDestLocation(gotoPos);
				}
				if (comp.size() != 0)
				{
				}
			}
		};
		//Advised to not call, only set
		virtual void End()  override {};

	private:

	};

	class EnemySpawn final : public dae::State
	{
	public:
		EnemySpawn() = default;
		virtual ~EnemySpawn() override {};
		std::string Name = "Spawn";
		std::string AnimatorClipName = "Destroy";
		Direction dir = up;
		dae::GridComponent* gridcomp;
		dae::AnimatorComponent* anim;
		float time;
		virtual void Entry() override
		{
			anim->PlayClip("Spawn");
		};
		//Advised to not call, only set
		virtual void Update() override
		{
			time += Time::GetInstance().DeltaTime();
			if (time > (anim->CurrentClip().EndFrame - anim->CurrentClip().StartFrame)*anim->CurrentClip().TickRate)
			{
				StateMachine->SetState("Wander");
			}
		};
		//Advised to not call, only set
		virtual void End()  override {};

	private:

	};


}