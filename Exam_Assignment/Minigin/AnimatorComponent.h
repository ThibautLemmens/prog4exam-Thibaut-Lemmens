#pragma once
#include "BaseComponent.h"
#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <tuple>
#include <SDL.h>

namespace dae
{
	struct Clip
	{
		std::string Name;
		int StartFrame;
		int EndFrame;
		float TickRate;
	};

	
	class AnimatorComponent final : public BaseComponent
	{
	public:
		AnimatorComponent(int col, int row) :m_Cols{col}, m_Rows{row}{};
		virtual ~AnimatorComponent() {};

		AnimatorComponent(const AnimatorComponent& other) = delete;
		AnimatorComponent(AnimatorComponent&& other) noexcept = delete;
		AnimatorComponent& operator=(const AnimatorComponent& other) = delete;
		AnimatorComponent& operator=(AnimatorComponent&& other) noexcept = delete;

		void AddClip(const std::string& ClipnName, const int& StartFrame,const int& EndFrame, const float& TickRate)
		{
			std::unordered_map<std::string, Clip>::iterator i = m_Clips.find(ClipnName);
			if (i != m_Clips.end())
			{
				Logger::LogError(L"Animation Clip Already Exists");
			}
			else
			{
				Clip newClip;
				newClip.Name = std::move(ClipnName);
				newClip.StartFrame = StartFrame;
				newClip.EndFrame = EndFrame;
				newClip.TickRate = TickRate;
				m_Clips.insert(std::pair<std::string, Clip>(ClipnName, newClip));
			}
		};

		void PlayClip(const std::string& clipname)
		{
			std::unordered_map<std::string, Clip>::iterator i = m_Clips.find(clipname);
			if (i == m_Clips.end())
			{
				Logger::LogError(L"Animation Clip does not Exists");
			}
			else
			{
				m_currentClip = &i->second;
				m_timer = 0;
			}
		};

		void Update()
		{
			m_timer += 0.16f;
			if (m_timer >= m_currentClip->TickRate)
			{
				m_timer -= m_currentClip->TickRate;
				m_CurrentFrame++;
				m_CurrentFrame = (m_CurrentFrame == m_currentClip->EndFrame) ? m_currentClip->StartFrame : m_CurrentFrame;
			}
		}

		SDL_Rect GetSource(const int& width,const int& Height)
		{
			int srcHeight, srcWidth;

			srcHeight = Height / m_Cols;
			srcWidth = width / m_Rows;

			SDL_Rect src;
			src.x = (m_CurrentFrame % m_Cols) * srcWidth;
			src.y = (m_CurrentFrame / (m_Cols + 1)) * srcHeight;
			src.w = srcWidth;
			src.h = srcHeight;
			return src;
		};
		
		//gets
		float TickRate() const { return m_tickRate; };
		int CurrentFrame() const { return m_CurrentFrame; };
		int Cols() const { return m_Cols; };
		int Rows() const { return m_Rows; };
		const Clip CurrentClip() const { return *m_currentClip; };

	private:
		int m_Cols, m_Rows;
		std::unordered_map<std::string, Clip> m_Clips;
		Clip* m_currentClip;

		float m_tickRate;
		float m_timer;
		int m_CurrentFrame;
	};
}