#include "Level.h"
#include "GameObject.h"
#include <string>
#include "TransformComponent.h"
#include "RenderTextureComponent.h"
#include "Scene.h"
#include "Renderer.h"
#include "ColliderComponent.h"

namespace dae
{
	Level::Level(Scene& scene) :
		m_Scene{ scene }
	{}

	void Level::AddLevelTile(const glm::ivec2& position, const std::string& texturePath)
	{
		// Create a new GameObject
		auto pTile{ std::make_shared<GameObject>() };

		m_pTransformComponents.emplace_back(pTile->AddComponent<TransformComponent>());
		m_pTransformComponents.back()->SetPosition(position);

		m_pRenderComponents.emplace_back(pTile->AddComponent<RenderTextureComponent>());
		m_pRenderComponents.back()->SetTexture(texturePath);

		pTile->AddComponent<ColliderComponent>()->SetDimensions(m_pRenderComponents.back()->GetTextureSize());

		// Add the GameObject to the scene
		m_Scene.Add(pTile);
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
			const auto& pos{ m_pTransformComponents.at(i)->GetWorldPosition() };
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
		}
	}
}
