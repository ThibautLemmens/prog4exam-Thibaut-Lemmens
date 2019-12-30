#pragma once
#include "BaseComponent.h"
#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <tuple>

struct SDL_Rect;

namespace dae
{
	//Clip = animation data
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
		//Give amount of rows and collums
		AnimatorComponent(int col, int row) :m_Cols{col}, m_Rows{row}{};
		virtual ~AnimatorComponent()
		{ 
			m_Clips.erase(m_Clips.begin(),m_Clips.end());
			//delete m_currentClip;
		};

		//Rule of 5
		AnimatorComponent(const AnimatorComponent& other) = delete;
		AnimatorComponent(AnimatorComponent&& other) noexcept = delete;
		AnimatorComponent& operator=(const AnimatorComponent& other) = delete;
		AnimatorComponent& operator=(AnimatorComponent&& other) noexcept = delete;

		//add animation clip <clipname> <startFrame> <endFrame> <speed>
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

				if (m_Clips.size() == 1)
				{
					PlayClip(ClipnName);
				}
			}
		};

		//play animation clip <clipname>
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
				m_CurrentFrame = (m_CurrentFrame >= m_currentClip->EndFrame + 1 || m_CurrentFrame <= m_currentClip->StartFrame - 1) ? m_currentClip->StartFrame : m_CurrentFrame;
			}
		};

		//Init
		virtual void Initialize() override {};

		//Update
		virtual void Update() override
		{
			m_timer += Time::GetInstance().DeltaTime();
			if (m_timer >= m_currentClip->TickRate)
			{
				m_timer = 0;
				m_CurrentFrame++;
				m_CurrentFrame = (m_CurrentFrame == m_currentClip->EndFrame+1) ? m_currentClip->StartFrame : m_CurrentFrame;
			}
		}

		//Retrun Source rectangle, pass texure <Widht> and <Height>
		SDL_Rect GetSource(const int& width,const int& Height);
		
		///gets
		//Get speed of active Clip
		float TickRate() const { return m_currentClip->TickRate; };
		//Get current frame 
		int CurrentFrame() const { return m_CurrentFrame; };
		//get amount of collums
		int Cols() const { return m_Cols; };
		//get amount of rows
		int Rows() const { return m_Rows; };
		//get current active clip
		const Clip CurrentClip() const { return *m_currentClip; };

	private:
		//collums and rows, max frames
		int m_Cols, m_Rows;
		//stored clips
		std::unordered_map<std::string, Clip> m_Clips;
		//current active clip
		Clip* m_currentClip;
		//timer used for animations
		float m_timer;
		//current frame showing
		int m_CurrentFrame;
	};
}