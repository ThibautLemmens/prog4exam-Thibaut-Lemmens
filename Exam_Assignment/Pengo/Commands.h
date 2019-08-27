#pragma once
#include "Command.h"
#include "GridManager.h"
#include "structs.h"
#include "GameObject.h"
namespace dae
{
	//player and enemy
	class MoveCommand final : public dae::Command
	{
	public:
		virtual void Execute() override
		{
			if (gridcomp->IsMoving() == false)
			{


				int gotoPos = 0;
				switch (pengoDir)
				{
				case up:
					gotoPos = gridcomp->GetPos() - 13;
					animator->PlayClip("RunUp");
					break;
				case down:
					gotoPos = gridcomp->GetPos() + 13;
					animator->PlayClip("RunDown");
					break;
				case left:
					gotoPos = gridcomp->GetPos() - 1;
					animator->PlayClip("Runleft");
					break;
				case right:
					gotoPos = gridcomp->GetPos() + 1;
					animator->PlayClip("RunRight");
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
				for (size_t i = 0; i < comp.size(); i++)
				{

				}
			}

		};
		Direction pengoDir;
		dae::GridComponent* gridcomp;
		dae::AnimatorComponent* animator;
	};



	class InteractCommand final : public dae::Command
	{
	public:
		virtual void Execute() override
		{
			if (gridcomp->IsMoving() == false)
			{
				std::string name = animator->CurrentClip().Name;

				if (name == "RunDown") pengoDir = down;
				if (name == "RunUp")pengoDir = up;
				if (name == "RunRight")pengoDir = right;
				if (name == "Runleft")pengoDir = left;

				int gotoPos = 0;
				switch (pengoDir)
				{
				case up:
					gotoPos = gridcomp->GetPos() - 13;
					animator->PlayClip("PushUp");
					break;
				case down:
					gotoPos = gridcomp->GetPos() + 13;
					animator->PlayClip("PushDown");
					break;
				case left:
					gotoPos = gridcomp->GetPos() - 1;
					animator->PlayClip("PushLeft");
					break;
				case right:
					gotoPos = gridcomp->GetPos() + 1;
					animator->PlayClip("PushRight");
					break;
				default:
					break;
				}

				auto comp = gridcomp->GetManager()->GetLocation(gotoPos);
				if (comp.size() != 0)
				{
					for (size_t i = 0; i < comp.size(); i++)
					{
						if (comp[i]->Tag() == "Block")
						{
							stateMachineComponent* x = comp[i]->GetGameObject()->GetComponent<stateMachineComponent>();
							if (x != nullptr) if (x->GetActiveStateName() != "Glide") x->SetState("Glide");
						}
						if (comp[i]->Tag() == "Wall")
						{
							stateMachineComponent* x = comp[i]->GetGameObject()->GetComponent<stateMachineComponent>();
							if (x != nullptr) x->SetState("wave");
						}
					}
				}

			}

		};
		Direction pengoDir;
		dae::GridComponent* gridcomp;
		dae::AnimatorComponent* animator;
	};

}