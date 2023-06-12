#pragma once
#include "Singleton.h"
#include "Level.h"
#include "PlayerComponent.h"
#include "EnemyBehavior.h"

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
		void StartGame();

		// Level management
		void AddLevel(std::unique_ptr<Level> level) { m_Levels.emplace_back(std::move(level)); }
		void LoadNextLevel();
		void LoadPreviousLevel();

		void AddPlayer(std::shared_ptr<GameObject> player);

		void AddEnemy(std::shared_ptr<GameObject> enemy);
		void RemoveEnemy(GameObject* pEnemy);
		void RemoveAllEnemies();

		bool IsLevelCompleted() const { return m_LevelCompleted; }

		// Score management
		void AddScore(int score, int playerId);
		int GetScore(int playerId) const { return playerId == 0 ? m_ScoreBub : m_ScoreBob; }
		int GetHighScore() const { return m_HighScore; }

		// Lives management
		int GetLives(int playerId) const { return playerId == 0 ? m_LivesBub : m_LivesBob; }
		void RemoveLife(int playerId) { playerId == 0 ? --m_LivesBub : --m_LivesBob; }

		const Level* GetCurrentLevel() const;
		const std::vector<PlayerComponent*>& GetPlayers() const { return m_pPlayerComponents; }
	private:
		GameMode m_GameMode{ GameMode::SinglePlayer };

		bool m_LevelCompleted{ false };

		int m_DeadEnemies{ 0 };

		// Persistent player data
		int m_HighScore{ 0 };
		int m_ScoreBob{ 0 };
		int m_ScoreBub{ 0 };

		int m_LivesBob{ 3 };
		int m_LivesBub{ 3 };

		// Level management
		int m_CurrentLevel{ -1 };
		std::vector<std::unique_ptr<Level>> m_Levels;

		std::vector<std::shared_ptr<GameObject>> m_pPlayers;
		std::vector<PlayerComponent*> m_pPlayerComponents;

		std::vector<std::shared_ptr<GameObject>> m_pEnemies;
		std::vector<EnemyBehavior*> m_pEnemyBehaviors;

		// Singleton
		explicit GameManager() = default;
		friend class Singleton<GameManager>;

		void SpawnPlayers();
		void SpawnEnemies();

		void CreateZenChan(const glm::vec2& pos);
		void CreateMaita(const glm::vec2& pos);
		void SaveHighScore();
	};
}
