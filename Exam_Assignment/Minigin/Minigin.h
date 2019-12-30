#pragma once
#include <future>
#include <mutex>
#include <atomic>
#include <condition_variable>
#include "RenderingStack.h"

struct SDL_Window;
class Prefabs;

namespace dae
{
	class Minigin
	{
		const int msPerFrame = 16; //16 for 60 fps, 33 for 30 fps
		SDL_Window* window{};
		//SDL_GLContext m_GLContext{};
	public:
		void Initialize();
		void LoadGame() const;
		void Cleanup();
		void Run();
		void Game();
		void CPU(const Camera &camera);
		void GPU();

	private:
		std::vector<std::future<void>> m_Futures;

		std::atomic<bool> m_GameFinishished = true;
		std::atomic<bool> m_CPUFinishished = true;
		std::atomic<bool> m_GPUFinishished = true;
		std::mutex m_GameMTX;
		std::mutex m_CPUMTX;
		std::mutex m_GPUMTX;
		std::condition_variable m_GameCV;
		std::condition_variable m_CPUCV;
		std::condition_variable m_GPUCV;

		std::atomic<bool> m_GameLoopComplete = true;
		std::mutex m_LoopMTX;
		std::condition_variable m_LoopCV;

		void FinishLoop(std::atomic<bool> &type);
		void startLoop();

	};
}