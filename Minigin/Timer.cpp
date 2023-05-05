#include "Timer.h"

namespace dae
{
	void Timer::Tick()
	{
		const auto currentTime{ std::chrono::high_resolution_clock::now() };
		m_DeltaTime = std::chrono::duration<float>(currentTime - m_LastTime).count();
		m_LastTime = currentTime;
	}
}
