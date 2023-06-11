#pragma once
#include "Singleton.h"
#include "Level.h"
#include "PlayerComponent.h"

namespace dae
{
	enum class GameMode
	{
		SinglePlayer,
		Coop,
		Versus
	};

	class GameManager final : public Singleton<GameManager>
	{
	public:

		// Level management
		void AddLevel(std::unique_ptr<Level> level) { m_Levels.emplace_back(std::move(level)); }
		void AddPlayer(PlayerComponent* player) { m_pPlayers.emplace_back(player); }
		void LoadNextLevel();
		void LoadPreviousLevel();

		void AddScore(int score, int playerId) { playerId == 0 ? m_ScoreBub += score : m_ScoreBob += score; }
		int GetScore(int playerId) const { return playerId == 0 ? m_ScoreBub : m_ScoreBob; }

		const Level* GetCurrentLevel() const;
		const std::vector<PlayerComponent*>& GetPlayers() const { return m_pPlayers; }

	private:
		GameMode m_GameMode{ GameMode::SinglePlayer };

		// Persistent player data
		int m_HighScore{ 0 };
		int m_ScoreBob{ 0 };
		int m_ScoreBub{ 0 };

		// Level management
		int m_CurrentLevel{ -1 };
		std::vector<std::unique_ptr<Level>> m_Levels;
		std::vector<PlayerComponent*> m_pPlayers;

		// Singleton
		explicit GameManager() = default;
		friend class Singleton<GameManager>;
	};
}
