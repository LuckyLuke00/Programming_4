#pragma once
#include <glm/glm.hpp>
#include <memory>
#include <string>
#include <vector>

namespace dae
{
	class ColliderComponent;
	class GameObject;
	class RenderTextureComponent;
	class Scene;
	class TransformComponent;

	class Level
	{
	public:
		explicit Level(Scene& scene);
		virtual ~Level() = default;

		Level(const Level& other) = delete;
		Level(Level&& other) noexcept = delete;
		Level& operator=(const Level& other) = delete;
		Level& operator=(Level&& other) noexcept = delete;

		void AddLevelTile(const glm::ivec2& position, const std::string& texturePath, bool smallTile = false);
		void ScaleToWindowSize();

		void Load();
		void Unload();

		// Getters and Setters
		const std::string& GetLevelFilePath() const { return m_LevelFilePath; }
		const std::string& GetLevelName() const { return m_LevelName; }
		float GetLevelScale() const { return m_Scale; }
		glm::ivec2 GetPlayerSpawnPosition(int index) const;

		void SetLevelFilePath(const std::string_view& path) { m_LevelFilePath = path; }
		void SetLevelName(const std::string_view& name) { m_LevelName = name; }
		void AddPlayerSpawnPosition(const glm::ivec2& position) { m_PlayerSpawnPositions.emplace_back(position); }
	private:
		std::string m_LevelName;
		std::string m_LevelFilePath;

		Scene& m_Scene;
		float m_Scale{ 1.f };

		// I chose to store the components in vectors, so I don't need to call a GetComponent for every tile
		// We're not in the hotcode path, so a GetComponent is not a big deal, but I still prefer to avoid it
		std::vector<RenderTextureComponent*> m_pRenderComponents;
		std::vector<TransformComponent*> m_pTransformComponents;
		std::vector<ColliderComponent*> m_pColliderComponents;

		std::vector<std::shared_ptr<GameObject>> m_pLevelTiles;
		std::vector<glm::ivec2> m_PlayerSpawnPositions;
	};
}
