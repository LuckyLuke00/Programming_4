#pragma once
#include "Singleton.h"

namespace dae
{
	class Time final : public Singleton<Time>
	{
	public:
		static float GetDeltaTime();
		static float GetTime();
		static int GetFPS();
		static void ToggleFPS(); // Temporary

		void Tick();

	private:
		float m_DeltaTime{ .01f };
		float m_LastTime{ .0f };

		// FPS Logic
		bool m_PrintFPS{ false }; // Temporary
		float m_FPSTimer{ .0f };
		float m_FPSUpdateInterval{ .5f };
		int m_FPS{ 0 };
		int m_FPSCount{ 0 };

		Time() = default;
		friend class Singleton<Time>;
	};
}
