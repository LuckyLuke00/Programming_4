#pragma once
#include "Component.h"
#include <string>
#include <glm/glm.hpp>

namespace dae
{
	class TransformComponent;
	class RenderSpriteComponent;
	class ColliderComponent;
	class PlayerComponent;
	class EnemyBehavior;
	struct SpriteAnimation;

	class BoulderComponent final : public Component
	{
	public:
		explicit BoulderComponent(GameObject* pOwner);
		~BoulderComponent() override = default;

		BoulderComponent(const BoulderComponent& other) = delete;
		BoulderComponent(BoulderComponent&& other) noexcept = delete;
		BoulderComponent& operator=(const BoulderComponent& other) = delete;
		BoulderComponent& operator=(BoulderComponent&& other) noexcept = delete;

		void Update() override;

		void SetInitialVelocity(float velocity) { m_InitialVelocity = velocity; }
		void AddAnimation(const std::string& name, const SpriteAnimation& animation);

		void ThrowBoulder(int direction);

	private:
		float m_LevelMargin{ 16.f };
		float m_MaxXPos{ 0.f };
		float m_MinXPos{ 0.f };
		float m_Direction{ 1.f };
		float m_InitialVelocity{ 100.f };
		glm::vec2 m_Velocity{ .0f, .0f };

		TransformComponent* m_pTransformComponent{ nullptr };
		RenderSpriteComponent* m_pRenderSpriteComponent{ nullptr };
		ColliderComponent* m_pColliderComponent{ nullptr };

		void OnTrigger(const GameObject* other);
		PlayerComponent* m_pHitPlayer{ nullptr };

		void CalculateBounds();
	};
}
