#include "MiniginPCH.h"
#include "FpsCounter.h"


void dae::FpsCounter::Update(float DeltaT)
{
	m_Timer += DeltaT;
	if (m_Timer > m_TimerInterval)
	{
		m_Timer -= m_TimerInterval;
		m_Text->SetText(std::to_string(m_Counter/m_Timer));
		m_Counter = 0;
	}
	m_Counter++;
	m_Text->Update(DeltaT);

}