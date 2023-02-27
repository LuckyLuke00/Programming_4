#include "Time.h"
#include <chrono>

namespace dae
{
	float Time::GetDeltaTime()
	{
		return GetInstance().m_DeltaTime;
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
	}
}
