#include "Level.h"
#include "GameObject.h"
#include <string>
#include "TransformComponent.h"
#include "RenderTextureComponent.h"
#include "Scene.h"
#include "Renderer.h"
#include "ColliderComponent.h"
#include "CollisionSystem.h"
#include "LevelLoader.h"

#include <iostream>

namespace dae
{
	Level::Level(Scene& scene) :
		m_Scene{ scene }
	{}

	void Level::AddLevelTile(const glm::ivec2& position, const std::string& texturePath, bool smallTile)
	{
		// Create a new GameObject
		m_pLevelTiles.emplace_back(std::make_shared<GameObject>());
		m_pLevelTiles.back()->SetActive(false);

		m_pTransformComponents.emplace_back(m_pLevelTiles.back()->AddComponent<TransformComponent>());
		m_pTransformComponents.back()->SetPosition(position);

		m_pRenderComponents.emplace_back(m_pLevelTiles.back()->AddComponent<RenderTextureComponent>());
		m_pRenderComponents.back()->SetTexture(texturePath);

		m_pColliderComponents.emplace_back(m_pLevelTiles.back()->AddComponent<ColliderComponent>());
		m_pColliderComponents.back()->SetDimensions(m_pRenderComponents.back()->GetTextureSize());
		m_pColliderComponents.back()->SetColliderType(smallTile ? ColliderType::OneWay : ColliderType::Normal);
	}

	void Level::ScaleToWindowSize()
	{
		// Get the height of the sdl window
		int width, height;
		Renderer::GetInstance().GetWindowSize(width, height);

		// Get the biggest vertical position of the level
		float biggestPosition{ .0f };
		float textureSize{ .0f };

		for (size_t i{}; i < m_pTransformComponents.size(); ++i)
		{
			const auto& pos{ m_pTransformComponents.at(i)->GetLocalPosition() };
			biggestPosition = std::max(std::max(pos.x, pos.y), biggestPosition);

			// Get the size of the texture
			// Get the render component at the same index as the transform component
			const auto pRenderComponent{ m_pRenderComponents.at(i)->GetTextureSize() };
			textureSize = std::min(pRenderComponent.x, pRenderComponent.y);
		}
		// Calculate the scale based on the height of the window and the biggest vertical position of the level
		// scale to the smallest height or width
		const float scale{ std::min(height, width) / (biggestPosition + textureSize) };

		for (auto* pTransformComponent : m_pTransformComponents)
		{
			// Round the scale to the nearest integer
			m_Scale = glm::round(scale);
			pTransformComponent->SetScale(m_Scale);
			pTransformComponent->SetPosition(pTransformComponent->GetLocalPosition() * m_Scale);
		}
	}

	void Level::Load()
	{
		// Load the level into memory if it isn't already loaded
		if (m_pLevelTiles.empty())
		{
			LevelLoader::LoadLevel(*this);
		}

		for (size_t i{}; i < m_pLevelTiles.size(); ++i)
		{
			CollisionSystem::GetInstance().AddCollider(m_pColliderComponents.at(i));
			m_pLevelTiles.at(i)->SetActive(true);
			m_Scene.Add(m_pLevelTiles.at(i));
		}
	}

	void Level::Unload()
	{
		for (size_t i{}; i < m_pLevelTiles.size(); ++i)
		{
			CollisionSystem::GetInstance().RemoveCollider(m_pColliderComponents.at(i));
			m_pLevelTiles.at(i)->SetActive(false);
			m_Scene.Remove(m_pLevelTiles.at(i));
		}
	}
	glm::ivec2 Level::GetPlayerSpawnPosition(int index) const
	{
		// If the vector is empty, return a default position
		if (m_PlayerSpawnPositions.empty())
		{
			return { 0,0 };
		}

		// If the index is negative return the first position
		if (index < 0)
		{
			return m_PlayerSpawnPositions.front();
		}

		// If the index is bigger than the size of the vector, return the last position
		if (index >= int(m_PlayerSpawnPositions.size()))
		{
			return m_PlayerSpawnPositions.back();
		}

		const auto& pos{ m_PlayerSpawnPositions.at(index) };

		// Return the position at the given index scaled to the window size
		return glm::ivec2(pos.x * m_Scale, pos.y * m_Scale);
	}
}
