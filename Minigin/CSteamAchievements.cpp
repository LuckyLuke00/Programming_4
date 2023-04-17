#include "CSteamAchievements.h"
#include <iostream>

namespace dae
{
	CSteamAchievements::CSteamAchievements() :
		m_CallbackUserStatsReceived{ this, &CSteamAchievements::OnUserStatsReceived },
		m_CallbackUserStatsStored{ this, &CSteamAchievements::OnUserStatsStored },
		m_CallbackAchievementStored{ this, &CSteamAchievements::OnAchievementStored },
		m_iAppID{ 0 },
		m_bInitialized{ false }
	{}

	void CSteamAchievements::Init(Achievement_t* Achievements, int NumAchievements)
	{
		m_iAppID = SteamUtils()->GetAppID();
		m_pAchievements = Achievements;
		m_iNumAchievements = NumAchievements;
		RequestStats();
	}

	bool CSteamAchievements::RequestStats() const
	{
		// Is Steam loaded? If not we can't get stats.
		if (nullptr == SteamUserStats() || nullptr == SteamUser())
		{
			return false;
		}
		// Is the user logged on?  If not we can't get stats.
		if (!SteamUser()->BLoggedOn())
		{
			return false;
		}
		// Request user stats.
		return SteamUserStats()->RequestCurrentStats();
	}

	bool CSteamAchievements::SetAchievement(const char* ID) const
	{
		// Have we received a call back from Steam yet?
		if (m_bInitialized)
		{
			SteamUserStats()->SetAchievement(ID);
			return SteamUserStats()->StoreStats();
		}
		// If not then we can't set achievements yet
		return false;
	}

	void CSteamAchievements::OnUserStatsReceived(UserStatsReceived_t* pCallback)
	{
		// we may get callbacks for other games' stats arriving, ignore them
		if (m_iAppID == static_cast<int64>(pCallback->m_nGameID))
		{
			if (k_EResultOK == pCallback->m_eResult)
			{
				std::cout << "Received stats and achievements from Steam\n";
				m_bInitialized = true;

				// load achievements
				for (int iAch = 0; iAch < m_iNumAchievements; ++iAch)
				{
					Achievement_t& ach = m_pAchievements[iAch];

					SteamUserStats()->GetAchievement(ach.m_pchAchievementID, &ach.m_bAchieved);
					_snprintf(ach.m_rgchName, sizeof(ach.m_rgchName), "%s",
						SteamUserStats()->GetAchievementDisplayAttribute(ach.m_pchAchievementID,
							"name"));
					_snprintf(ach.m_rgchDescription, sizeof(ach.m_rgchDescription), "%s",
						SteamUserStats()->GetAchievementDisplayAttribute(ach.m_pchAchievementID,
							"desc"));
				}
			}
			else
			{
				char buffer[128];
				_snprintf(buffer, 128, "RequestStats - failed, %d\n", pCallback->m_eResult);
				std::cout << buffer << '\n';
			}
		}
	}

	void CSteamAchievements::OnUserStatsStored(UserStatsStored_t* pCallback)
	{
		// we may get callbacks for other games' stats arriving, ignore them
		if (m_iAppID == static_cast<int64>(pCallback->m_nGameID))
		{
			if (k_EResultOK == pCallback->m_eResult)
			{
				std::cout << "Stored stats for Steam\n";
			}
			else
			{
				char buffer[128];
				_snprintf(buffer, 128, "StatsStored - failed, %d\n", pCallback->m_eResult);
				std::cout << buffer << '\n';
			}
		}
	}

	void CSteamAchievements::OnAchievementStored(UserAchievementStored_t* pCallback)
	{
		// we may get callbacks for other games' stats arriving, ignore them
		if (m_iAppID == static_cast<int64>(pCallback->m_nGameID))
		{
			std::cout << "Stored Achievement for Steam\n";
		}
	}
}
