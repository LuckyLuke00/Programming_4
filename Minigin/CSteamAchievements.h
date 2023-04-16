#pragma once
#include "steam_api.h"
#include "Achievement.h"
#include "Singleton.h"

namespace dae
{
	class CSteamAchievements final : public Singleton<CSteamAchievements>
	{
	public:
		void Init(Achievement_t* Achievements, int NumAchievements);

		bool RequestStats() const;
		bool SetAchievement(const char* ID) const;

		STEAM_CALLBACK(CSteamAchievements, OnUserStatsReceived, UserStatsReceived_t,
			m_CallbackUserStatsReceived);
		STEAM_CALLBACK(CSteamAchievements, OnUserStatsStored, UserStatsStored_t,
			m_CallbackUserStatsStored);
		STEAM_CALLBACK(CSteamAchievements, OnAchievementStored,
			UserAchievementStored_t, m_CallbackAchievementStored);

	private:
		int64 m_iAppID; // Our current AppID
		Achievement_t* m_pAchievements; // Achievements data
		int m_iNumAchievements; // The number of Achievements
		bool m_bInitialized; // Have we called Request stats and received the callback?

		CSteamAchievements();
		friend class Singleton<CSteamAchievements>;
	};
}
