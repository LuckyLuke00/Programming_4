#pragma once
#include "Singleton.h"
#include "Level.h"

namespace dae
{
	class GameManager final : public Singleton<GameManager>
	{
	public:

		// Level management
		void AddLevel(std::unique_ptr<Level> level) { m_Levels.emplace_back(std::move(level)); }
		void LoadNextLevel();
		void LoadPreviousLevel();

		// Const getter for the current level
		const Level& GetCurrentLevel() const { return *m_Levels[m_CurrentLevel]; }

	private:
		int m_CurrentLevel{ -1 };
		std::vector<std::unique_ptr<Level>> m_Levels;

		explicit GameManager() = default;
		friend class Singleton<GameManager>;
	};
}
