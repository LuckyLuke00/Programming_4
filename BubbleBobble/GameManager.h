#pragma once
#include "Singleton.h"
#include "Level.h"
#include "PlayerComponent.h"

namespace dae
{
	class GameManager final : public Singleton<GameManager>
	{
	public:

		// Level management
		void AddLevel(std::unique_ptr<Level> level) { m_Levels.emplace_back(std::move(level)); }
		void AddPlayer(PlayerComponent* player) { m_pPlayers.emplace_back(player); }
		void LoadNextLevel();
		void LoadPreviousLevel();

		// Const getter for the current level
		const Level* GetCurrentLevel() const;

	private:
		int m_CurrentLevel{ -1 };
		std::vector<std::unique_ptr<Level>> m_Levels;
		std::vector<PlayerComponent*> m_pPlayers;

		explicit GameManager() = default;
		friend class Singleton<GameManager>;
	};
}
