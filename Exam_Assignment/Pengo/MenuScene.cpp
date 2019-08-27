#include "pch.h"
#include "MenuScene.h"
#include "Components.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "Commands.h"
#include "States.h"
#include "InputManager.h"
#include "PengoScene.h"
#include "PengoCOOPScene.h"

namespace dae
{

	class aCommand final : public dae::Command
	{
	public:
		virtual void Execute() override
		{
			SceneManager::GetInstance().Empty();
			SceneManager::GetInstance().AddScene(new PengoScene);

		};
	};
	class bCommand final : public dae::Command
	{
	public:
		virtual void Execute() override
		{
			SceneManager::GetInstance().Empty();
			SceneManager::GetInstance().AddScene(new PengoCOOPScene);

		};
	};


	MenuScene::MenuScene()
	{

		dae::ResourceManager::GetInstance().StoreTexture("Menu", dae::ResourceManager::GetInstance().LoadTexture("Menu.jpg"));
		//dae::ResourceManager::GetInstance().StoreTexture("Pengu", dae::ResourceManager::GetInstance().LoadTexture("Pengu"));

		GameObject* press = new GameObject;
		InputComponent* inputcomp = new InputComponent(0, &InputManager::GetInstance());

		Input* normal = new Input;
		normal->button = ControllerButton::ButtonA;
		normal->keyboard = 'A';
		normal->pCommand = new aCommand();
		inputcomp->AddInput(normal);

		Input* coop = new Input;
		coop->button = ControllerButton::ButtonB;
		coop->keyboard = 'B';
		coop->pCommand = new bCommand();
		inputcomp->AddInput(coop);

		press->AddComponent(inputcomp);

		dae::RenderComponent* PlayerRender = GetSceneRenderer()->GetComponent(press->Transform());

		PlayerRender->Texture(dae::ResourceManager::GetInstance().GetTexture("Menu"));
		Add(press);

	}


	MenuScene::~MenuScene()
	{
	}


}