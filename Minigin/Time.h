#pragma once
#include "Singleton.h"
#include <chrono>

namespace dae
{
	class Time final : public Singleton<Time>
	{
	public:
		static float GetDeltaTime();

		void Tick();

	private:
		float m_DeltaTime{ .01f };
		std::chrono::time_point<std::chrono::high_resolution_clock> m_LastTime{ std::chrono::high_resolution_clock::now() };

		Time() = default;
		friend class Singleton<Time>;
	};
}
