#pragma once
#include "Singleton.h"
#include <chrono>

namespace dae
{
	class Time final : public Singleton<Time>
	{
	public:
		static float GetDeltaSeconds() { return GetInstance().m_DeltaTime; }
		static std::chrono::time_point<std::chrono::high_resolution_clock> GetLastTime() { return GetInstance().m_LastTime; }

		void Tick();

	private:
		float m_DeltaTime{ .0f };
		std::chrono::time_point<std::chrono::high_resolution_clock> m_LastTime{ std::chrono::high_resolution_clock::now() };

		Time() = default;
		friend class Singleton<Time>;
	};
}
