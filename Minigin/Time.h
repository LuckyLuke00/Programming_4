#pragma once
#include "Singleton.h"

namespace dae
{
	class Time final : public Singleton<Time>
	{
	public:
		static float GetDeltaTime();
		static float GetTime();

		void Tick();

	private:
		float m_DeltaTime{ .01f };
		float m_LastTime{ .0f };

		Time() = default;
		friend class Singleton<Time>;
	};
}
