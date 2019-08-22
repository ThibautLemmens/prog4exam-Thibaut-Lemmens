#pragma once
#include "Singleton.h"
#include <chrono>

namespace dae
{
	class Time final : public Singleton<Time>
	{
	public:
		Time() 
		{
			StartTime = std::chrono::high_resolution_clock::now();
		};

		void Update()
		{
			auto currentTime = std::chrono::high_resolution_clock::now();
			m_deltaTime = std::chrono::duration<float>(currentTime - StartTime).count();
			StartTime = currentTime;
			m_deltaTime *= m_TimeMultiplier;
		};

		//get
		float FPS()const { return 1 / m_deltaTime; }
		float DeltaTime()const { return m_deltaTime; };
		float TimeMultiplier()const { return m_TimeMultiplier; };

		//set
		void TimeMultiplier(float timeMultiply) { m_TimeMultiplier = timeMultiply; };

	private:
		float m_deltaTime;
		float m_TimeMultiplier = 1;
		std::chrono::steady_clock::time_point StartTime;
	};
}