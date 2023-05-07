#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <string>

namespace dae
{
	class Scene;
	class RenderTextureComponent;
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

		// Getters and Setters
		void AddLevelTile(const glm::ivec2& position, const std::string& texturePath);
		void ScaleToWindowSize();
		float GetLevelScale() const { return m_Scale; }
	private:
		Scene& m_Scene;
		float m_Scale{ 1.f };

		std::vector<RenderTextureComponent*> m_pRenderComponents;
		std::vector<TransformComponent*> m_pTransformComponents;
	};
}