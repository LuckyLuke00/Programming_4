#include "GameManager.h"

namespace dae
{
	void GameManager::LoadNextLevel()
	{
		if (m_Levels.empty()) return; // No levels added yet

		if (m_CurrentLevel != -1) m_Levels[m_CurrentLevel]->Unload();

		// If we are at the last level, go back to the first
		m_CurrentLevel = m_CurrentLevel == static_cast<int>(m_Levels.size() - 1) ? 0 : m_CurrentLevel + 1;

		m_Levels[m_CurrentLevel]->Load();

		for (const auto& pPlayer : m_pPlayers) pPlayer->Respawn();
	}

	void GameManager::LoadPreviousLevel()
	{
		if (m_Levels.empty()) return; // No levels added yet

		if (m_CurrentLevel != -1) m_Levels[m_CurrentLevel]->Unload();

		// If we are at the first level, go to the last
		m_CurrentLevel = m_CurrentLevel == 0 ? static_cast<int>(m_Levels.size() - 1) : m_CurrentLevel - 1;

		m_Levels[m_CurrentLevel]->Load();

		for (const auto& pPlayer : m_pPlayers) pPlayer->Respawn();
	}

	void GameManager::AddScore(int score, int playerId)
	{
		playerId == 0 ? m_ScoreBub += score : m_ScoreBob += score;

		// Check if we have a new high score
		if (m_ScoreBub > m_HighScore) m_HighScore = m_ScoreBub;
		if (m_ScoreBob > m_HighScore) m_HighScore = m_ScoreBob;
	}

	const Level* GameManager::GetCurrentLevel() const
	{
		if (m_CurrentLevel < 0 || m_CurrentLevel >= static_cast<int>(m_Levels.size())) return nullptr;
		return m_Levels[m_CurrentLevel].get();
	}
}
