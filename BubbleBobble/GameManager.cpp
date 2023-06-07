#include "GameManager.h"

namespace dae
{
	void GameManager::LoadNextLevel()
	{
		if (m_Levels.empty()) return; // No levels added yet

		if (m_CurrentLevel != -1) m_Levels[m_CurrentLevel]->Unload();

		// If we are at the last level, go back to the first
		m_CurrentLevel = m_CurrentLevel == m_Levels.size() - 1 ? 0 : m_CurrentLevel + 1;

		m_Levels[m_CurrentLevel]->Load();
	}

	void GameManager::LoadPreviousLevel()
	{
		if (m_Levels.empty()) return; // No levels added yet

		if (m_CurrentLevel != -1) m_Levels[m_CurrentLevel]->Unload();

		// If we are at the first level, go to the last
		m_CurrentLevel = m_CurrentLevel == 0 ? static_cast<int>(m_Levels.size() - 1) : m_CurrentLevel - 1;

		m_Levels[m_CurrentLevel]->Load();
	}
}
