#pragma once
#include "Singleton.h"
#include <chrono>

namespace dae
{
	class Timer final : public Singleton<Timer>
	{
	public:
		static float GetDeltaSeconds() { return GetInstance().m_DeltaTime; }
		static std::chrono::time_point<std::chrono::high_resolution_clock> GetLastTime() { return GetInstance().m_LastTime; }

		void Tick();

	private:
		float m_DeltaTime{ .0f };
		std::chrono::time_point<std::chrono::high_resolution_clock> m_LastTime{ std::chrono::high_resolution_clock::now() };

		Timer() = default;
		friend class Singleton<Timer>;
	};
}
