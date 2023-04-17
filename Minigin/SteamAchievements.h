#pragma once
#include "steam_api.h"
#include "Achievement.h"
#include "CSteamAchievements.h"

namespace dae
{
	// Defining our achievements
	enum EAchievements
	{
		ACH_WIN_ONE_GAME = 0,
		ACH_WIN_100_GAMES = 1,
		ACH_TRAVEL_FAR_ACCUM = 2,
		ACH_TRAVEL_FAR_SINGLE = 3,
		NEW_ACHIEVEMENT_0_4 = 4,
	};

	// Achievement array which will hold data about the achievements and their state
	Achievement_t g_Achievements[] =
	{
		_ACH_ID(ACH_WIN_ONE_GAME, "Winner"),
		_ACH_ID(ACH_WIN_100_GAMES, "Champion"),
		_ACH_ID(ACH_TRAVEL_FAR_ACCUM, "Interstellar"),
		_ACH_ID(ACH_TRAVEL_FAR_SINGLE, "Orbiter"),
		_ACH_ID(NEW_ACHIEVEMENT_0_4, "Hidden"),
	};

	// Global access to Achievements object
	CSteamAchievements* g_SteamAchievements = nullptr;
}
