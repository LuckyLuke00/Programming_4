#include "GameManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "GameObject.h"
#include "Level.h"
#include "RenderSpriteComponent.h"
#include <algorithm>
#include "ZenChanBehavior.h"
#include "MaitaBehavior.h"

namespace dae
{
	void GameManager::StartGame()
	{
		SpawnPlayers();
	}

	void GameManager::LoadNextLevel()
	{
		if (m_Levels.empty()) return; // No levels added yet

		m_LevelCompleted = false;
		m_DeadEnemies = 0;

		if (m_CurrentLevel != -1) m_Levels[m_CurrentLevel]->Unload();

		RemoveAllEnemies();

		//auto bubbles{ SceneManager::GetInstance().GetActiveScene()->FindObjectsWithTag("Bubble") };
		//for (const auto& pBubble : bubbles) pBubble->MarkForDelete();

		//auto pickups{ SceneManager::GetInstance().GetActiveScene()->FindObjectsWithTag("Pickup") };
		//for (const auto& pPickup : pickups) pPickup->MarkForDelete();

		// If we are at the last level, go back to the first
		m_CurrentLevel = m_CurrentLevel == static_cast<int>(m_Levels.size() - 1) ? 0 : m_CurrentLevel + 1;

		m_Levels[m_CurrentLevel]->Load();

		for (const auto& pPlayer : m_pPlayerComponents) pPlayer->Respawn();

		SpawnEnemies();
	}

	void GameManager::LoadPreviousLevel()
	{
		if (m_Levels.empty()) return; // No levels added yet

		m_LevelCompleted = false;
		m_DeadEnemies = 0;

		if (m_CurrentLevel != -1) m_Levels[m_CurrentLevel]->Unload();

		RemoveAllEnemies();

		// If we are at the first level, go to the last
		m_CurrentLevel = m_CurrentLevel == 0 ? static_cast<int>(m_Levels.size() - 1) : m_CurrentLevel - 1;

		m_Levels[m_CurrentLevel]->Load();

		for (const auto& pPlayer : m_pPlayerComponents) pPlayer->Respawn();

		SpawnEnemies();
	}

	void GameManager::AddPlayer(std::shared_ptr<GameObject> player)
	{
		m_pPlayers.emplace_back(std::move(player));
		auto playerComp{ m_pPlayers.back()->GetComponent<PlayerComponent>() };
		m_pPlayerComponents.emplace_back(playerComp);
	}

	void GameManager::AddEnemy(std::shared_ptr<GameObject> enemy)
	{
		m_pEnemies.emplace_back(std::move(enemy));
		m_pEnemyBehaviors.emplace_back(m_pEnemies.back()->GetComponent<EnemyBehavior>());
	}

	void GameManager::RemoveEnemy(GameObject*)
	{
		//for (int i{ 0 }; i < static_cast<int>(m_pEnemies.size()); ++i)
		//{
		//	if (m_pEnemies[i].get() == pEnemy)
		//	{
		//		m_pEnemies.erase(m_pEnemies.begin() + i);
		//		m_pEnemyBehaviors.erase(m_pEnemyBehaviors.begin() + i);
		//		pEnemy->MarkForDelete();
		//		if (m_pEnemies.empty()) m_LevelCompleted = true;
		//		return;
		//	}
		//}
		//++m_DeadEnemies;
		//if (m_DeadEnemies == static_cast<int>(m_pEnemies.size())) m_LevelCompleted = true;
	}

	void GameManager::RemoveAllEnemies()
	{
		if (m_pEnemies.empty()) return;

		for (const auto& pEnemy : m_pEnemies)
		{
			pEnemy->MarkForDelete();
		}

		m_pEnemies.clear();
		m_pEnemyBehaviors.clear();
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

	void GameManager::SpawnPlayers()
	{
		for (const auto& pPlayer : m_pPlayers)
		{
			SceneManager::GetInstance().GetActiveScene()->Add(pPlayer);
		}
	}
	void GameManager::SpawnEnemies()
	{
		auto level{ m_Levels[m_CurrentLevel].get() };
		const auto& spawnPos{ level->GetEnemySpawnPositions() };

		for (const auto& spawn : spawnPos)
		{
			if (spawn.second == EnemyType::ZenChan) CreateZenChan(spawn.first);
			else if (spawn.second == EnemyType::Maita) CreateMaita(spawn.first);
		}
	}

	void GameManager::CreateZenChan(const glm::vec2& pos)
	{
		// Zen-chan Animations
		SpriteAnimation walkZenChan;
		walkZenChan.rows = 2;
		walkZenChan.cols = 2;
		walkZenChan.fps = 6;
		walkZenChan.frames = 4;

		SpriteAnimation bubbleZenChan;
		bubbleZenChan.rows = 1;
		bubbleZenChan.cols = 3;
		bubbleZenChan.fps = 6;
		bubbleZenChan.frames = 3;

		SpriteAnimation deathZenChan;
		deathZenChan.rows = 2;
		deathZenChan.cols = 2;
		deathZenChan.fps = 6;
		deathZenChan.frames = 4;

		// Zen-chan
		auto zenChan{ std::make_shared<GameObject>() };
		auto zenChanComponent{ zenChan->AddComponent<ZenChanBehavior>() };
		zenChanComponent->Spawn(pos);

		// Zen-chan: Animation Textures
		walkZenChan.SetTexture("Sprites/Enemies/ZenChan/zenchan_walk.png");
		bubbleZenChan.SetTexture("Sprites/Enemies/ZenChan/zenchan_bubble.png");
		deathZenChan.SetTexture("Sprites/Enemies/ZenChan/zenchan_death.png");

		// Zen-chan: Add Animations
		zenChanComponent->AddAnimation("Walk", walkZenChan);
		zenChanComponent->AddAnimation("Bubble", bubbleZenChan);
		zenChanComponent->AddAnimation("Death", deathZenChan);

		AddEnemy(zenChan);
		SceneManager::GetInstance().GetActiveScene()->Add(std::move(zenChan));
	}

	void GameManager::CreateMaita(const glm::vec2& pos)
	{
		// Maita Animations
		SpriteAnimation walkMaita;
		walkMaita.rows = 1;
		walkMaita.cols = 5;
		walkMaita.fps = 12;
		walkMaita.frames = 5;

		SpriteAnimation bubbleMaita;
		bubbleMaita.rows = 1;
		bubbleMaita.cols = 3;
		bubbleMaita.fps = 6;
		bubbleMaita.frames = 3;

		SpriteAnimation deathMaita;
		deathMaita.rows = 2;
		deathMaita.cols = 2;
		deathMaita.fps = 6;
		deathMaita.frames = 4;

		// Maita
		auto maita{ std::make_shared<GameObject>() };
		auto maitaComponent{ maita->AddComponent<MaitaBehavior>() };
		maitaComponent->Spawn(pos);

		// Maita: Animation Textures
		walkMaita.SetTexture("Sprites/Enemies/Maita/maita_walk.png");
		bubbleMaita.SetTexture("Sprites/Enemies/Maita/maita_bubble.png");
		deathMaita.SetTexture("Sprites/Enemies/Maita/maita_death.png");

		// Maita: Add Animations
		maitaComponent->AddAnimation("Walk", walkMaita);
		maitaComponent->AddAnimation("Bubble", bubbleMaita);
		maitaComponent->AddAnimation("Death", deathMaita);

		AddEnemy(maita);
		SceneManager::GetInstance().GetActiveScene()->Add(std::move(maita));
	}
}
