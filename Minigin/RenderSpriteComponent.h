#pragma once
#include "RenderComponent.h"
#include "Texture2D.h"
#include <memory>
#include <string>
#include <unordered_map>
#include "ResourceManager.h"

namespace dae
{
	class TransformComponent;

	struct SpriteAnimation
	{
		int rows{ -1 };
		int cols{ -1 };

		int fps{ -1 };
		int frames{ -1 };

		float totalTime{ .0f };

		std::shared_ptr<Texture2D> m_Texture{};

		void SetTexture(const std::string& filename) { m_Texture = ResourceManager::GetInstance().LoadTexture(filename); }
	};

	class RenderSpriteComponent final : public RenderComponent
	{
	public:
		explicit RenderSpriteComponent(GameObject* pOwner);
		~RenderSpriteComponent() override = default;

		RenderSpriteComponent(const RenderSpriteComponent& other) = delete;
		RenderSpriteComponent(RenderSpriteComponent&& other) noexcept = delete;
		RenderSpriteComponent& operator=(const RenderSpriteComponent& other) = delete;
		RenderSpriteComponent& operator=(RenderSpriteComponent&& other) noexcept = delete;

		void Render() override;

		void AddAnimation(const std::string& name, const SpriteAnimation& animation);
		void SetAnimation(const std::string& name);

		glm::vec2 GetFrameSize() const;

	private:
		TransformComponent* m_pTransformComponent{ nullptr };

		// Container for all the animations
		std::unordered_map<std::string, SpriteAnimation> m_Animations{};

		// Current animation
		SpriteAnimation* m_pCurrentAnimation{ nullptr };
	};
}
