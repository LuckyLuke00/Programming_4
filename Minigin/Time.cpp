#include "Time.h"
#include <chrono>
#include <iostream>

namespace dae
{
	float Time::GetDeltaTime()
	{
		return GetInstance().m_DeltaTime;
	}

	int Time::GetFPS()
	{
		return GetInstance().m_FPS;
	}

	void Time::ToggleFPS()
	{
		GetInstance().m_PrintFPS = !GetInstance().m_PrintFPS;
	}

	float Time::GetTime()
	{
		const auto now{ std::chrono::high_resolution_clock::now() };
		const auto duration{ now.time_since_epoch() };
		return static_cast<float>(std::chrono::duration_cast<std::chrono::milliseconds>(duration).count()) / 1000.f;
	}

	void Time::Tick()
	{
		m_DeltaTime = GetTime() - m_LastTime;
		m_LastTime = GetTime();

		m_FPSTimer += m_DeltaTime;
		++m_FPSCount;
		if (m_FPSTimer >= m_FPSUpdateInterval)
		{
			m_FPS = m_FPSCount;
			m_FPSCount = 0;
			m_FPSTimer = .0f;

			if (m_PrintFPS) std::cout << "FPS: " << m_FPS << '\n';
		}
	}
}
