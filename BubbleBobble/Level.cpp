#include "Level.h"
#include "GameObject.h"
#include <string>
#include "TransformComponent.h"
#include "RenderTextureComponent.h"
#include "Scene.h"
#include "Renderer.h"

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

		// Add the GameObject to the scene
		m_Scene.Add(pTile);
	}

	void Level::ScaleToWindowSize()
	{
		// Get the height of the sdl window
		int width, height;
		Renderer::GetInstance().GetWindowSize(width, height);

		// Get the biggest vertical position of the level
		float biggestVerticalPosition{ .0f };
		float textureSize{ .0f };

		for (size_t i{}; i < m_pTransformComponents.size(); ++i)
		{
			if (m_pTransformComponents.at(i)->GetWorldPosition().y > biggestVerticalPosition)
			{
				biggestVerticalPosition = m_pTransformComponents.at(i)->GetWorldPosition().y;

				// Get the size of the texture
				// Get the render component at the same index as the transform component
				const auto* pRenderComponent{ m_pRenderComponents.at(i) };
				textureSize = pRenderComponent->GetTextureSize().y;
			}
		}

		for (auto* pTransformComponent : m_pTransformComponents)
		{
			// Calculate the scale based on the height of the window and the biggest vertical position of the level
			// scale to the smallest height or width
			const float scale{ std::min(height, width) / (biggestVerticalPosition + textureSize) };

			// Round the scale to the nearest integer
			m_Scale = glm::round(scale);
			pTransformComponent->SetScale(m_Scale);
		}
	}
}
