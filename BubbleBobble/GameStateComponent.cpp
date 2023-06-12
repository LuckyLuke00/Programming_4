#include "GameStateComponent.h"
#include "GameManager.h"
#include "Timer.h"

namespace dae
{
	GameStateComponent::GameStateComponent(GameObject* pOwner) :
		Component{ pOwner }
	{
	}

	void GameStateComponent::Update()
	{
		if (!GameManager::GetInstance().IsLevelCompleted()) return;

		m_LevelCompleteTimer += Timer::GetDeltaSeconds();

		if (m_LevelCompleteTimer >= m_LevelCompleteTime)
		{
			GameManager::GetInstance().LoadNextLevel();
			m_LevelCompleteTimer = .0f;
		}
	}
}
