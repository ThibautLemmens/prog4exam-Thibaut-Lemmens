#pragma once
#include "TextObject.h"

namespace dae
{
	class FpsCounter final : public SceneObject
	{
	public:
		virtual void Update() override;

	private:
		Font* m_Font;
		TextObject* m_Text;
		
		unsigned int m_Counter=0;
		float m_Timer=0;
		float m_TimerInterval=1;

	};

}