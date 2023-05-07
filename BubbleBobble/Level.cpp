#include "Level.h"
#include "GameObject.h"
#include <string>
#include "TransformComponent.h"
#include "RenderTextureComponent.h"
#include "Scene.h"


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
}
