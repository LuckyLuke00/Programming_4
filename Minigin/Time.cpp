#include "Time.h"

namespace dae
{
	void Time::Tick()
	{
		const auto currentTime{ std::chrono::high_resolution_clock::now() };
		m_DeltaTime = std::chrono::duration<float>(currentTime - m_LastTime).count();
		m_LastTime = currentTime;
	}
}