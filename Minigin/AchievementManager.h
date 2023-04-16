#pragma once
#include "Singleton.h"
#include "Observer.h"
#include "EventManager.h"
#include <iostream>

namespace dae
{
	class AchievementManager final : public Singleton<AchievementManager>
	{
	private:
		friend class Singleton<AchievementManager>;
		explicit AchievementManager()
		{
			// Subscribe to PointsUpdated event with callback function
			EventManager::GetInstance().Subscribe("PointsUpdated", std::bind_front(&AchievementManager::OnPointsUpdated, this));
		}

		void OnPointsUpdated(Event*, std::any eventData) const
		{
			if (std::any_cast<int>(eventData) < 500) return;
			CSteamAchievements::GetInstance().SetAchievement("ACH_WIN_ONE_GAME");
		}
	};
}
