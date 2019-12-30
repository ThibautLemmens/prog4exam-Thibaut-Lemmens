#include "MiniginPCH.h"
#include "Minigin.h"
#include "Time.h"
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL.h>
//#include "TextObject.h"
#include "GameObject.h"
#include "Scene.h"
//#include "Logger.h"
#include <glew.h>


void dae::Minigin::Initialize()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	window = SDL_CreateWindow(
		"Lexil",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		416,
		680,
		SDL_WINDOW_OPENGL
	);

	if (window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(window);

	InputManager::GetInstance().Init();
}

/**
 * Code constructing the scene world starts here
 */
void dae::Minigin::LoadGame() const
{
	//dae::SceneManager::GetInstance().AddScene(new MenuScene());
}

void dae::Minigin::Cleanup()
{
	m_Futures.clear();
	Renderer::GetInstance().Destroy();
	//SDL_GL_DeleteContext(m_GLContext);
	SDL_DestroyWindow(window);
	window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run()
{
	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Resources/");

	LoadGame();

	{
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();
		auto& time = Time::GetInstance();
		auto& renderStack = RenderingStack::GetInstance();
		Camera camera;

		//make game loop threads
		m_Futures.push_back(std::async(std::launch::async, &Minigin::Game, this));
		m_Futures.push_back(std::async(std::launch::async, &Minigin::CPU, this, camera));
		m_Futures.push_back(std::async(std::launch::async, &Minigin::GPU, this));

		bool doContinue = true;
		while (doContinue)
		{
			//update time
			time.Update();
			//get input
			doContinue = input.ProcessInput();

			//game, cpu and gpu multi-threaded
			startLoop();

			//wait until loop is finished
			std::unique_lock<std::mutex> lk(m_LoopMTX);
			m_LoopCV.wait(lk, [this] {return !m_GameLoopComplete; });
			lk.unlock();

			//clear and swap buffer
			renderStack.ClearBuffer();
			renderStack.Swap();

			//wait for X to cap fps
			float t{ 0.16f - time.DeltaTime() };
			std::this_thread::sleep_for(std::chrono::milliseconds(long long(t)));
		}
	}
	Cleanup();
}

void dae::Minigin::Game()
{
	while (true)
	{
		std::unique_lock<std::mutex> lk(m_GameMTX);
		m_GameCV.wait(lk, [this] {return !m_GameFinishished; });
		
		//game Update
		SceneManager::GetInstance().Update();
		FinishLoop(m_GameFinishished);

		lk.unlock();
	}
}

void dae::Minigin::CPU(const Camera &camera)
{
	while (true)
	{
		std::unique_lock<std::mutex> lk(m_CPUMTX);
		m_CPUCV.wait(lk, [this] {return !m_CPUFinishished; });
		
		//CPU Update
		SceneManager::GetInstance().Render();
		RenderingStack::GetInstance().CLip(camera);
		FinishLoop(m_CPUFinishished);
		
		lk.unlock();
	}
	
}

void dae::Minigin::GPU()
{
	while (true)
	{
		std::unique_lock<std::mutex> lk(m_GPUMTX);
		m_GPUCV.wait(lk, [this] {return !m_GPUFinishished; });
		
		//GPU update
		RenderingStack::GetInstance().DrawBuffer();
		FinishLoop(m_GPUFinishished);
		
		lk.unlock();
	}
}

void dae::Minigin::FinishLoop(std::atomic<bool> &type)
{
	type = true;

	if (m_GameFinishished && m_CPUFinishished && m_GPUFinishished)
	{
		m_GameLoopComplete = true;
	}
}

void dae::Minigin::startLoop()
{
	 m_GameFinishished = false;
	 m_CPUFinishished = false;
	 m_GPUFinishished = false;
	 m_GameLoopComplete = false;
}
