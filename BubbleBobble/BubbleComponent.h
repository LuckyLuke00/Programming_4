#pragma once
#include "Component.h"
#include <glm/glm.hpp>
#include <string>

namespace dae
{
	class TransformComponent;
	class RenderSpriteComponent;
	class ColliderComponent;
	class EnemyBehavior;
	struct SpriteAnimation;

	class BubbleComponent final : public Component
	{
	public:
		explicit BubbleComponent(GameObject* pOwner);
		~BubbleComponent() override = default;

		BubbleComponent(const BubbleComponent& other) = delete;
		BubbleComponent(BubbleComponent&& other) noexcept = delete;
		BubbleComponent& operator=(const BubbleComponent& other) = delete;
		BubbleComponent& operator=(BubbleComponent&& other) noexcept = delete;

		void Update() override;

		void SetInitialVelocity(float velocity) { m_InitialVelocity = velocity; }
		void AddAnimation(const std::string& name, const SpriteAnimation& animation);

		void BlowBubble(int direction);
		void OnTrigger(const GameObject* other);
		void PopBubble();

	private:
		bool m_IsBlowing{ false };
		float m_InitialVelocity{ 500.f };
		float m_Deceleration{ 1'000.f };
		float m_Direction{ 1.f };
		float m_RiseSpeed{ 100.f };
		float m_MaxYPos{ 145.f };

		float m_BubbleTimer{ 0.f };
		float m_BubbleTime{ 5.f };
		glm::vec2 m_Velocity{ .0f, .0f };

		TransformComponent* m_pTransformComponent{ nullptr };
		RenderSpriteComponent* m_pRenderSpriteComponent{ nullptr };
		ColliderComponent* m_pColliderComponent{ nullptr };
		EnemyBehavior* m_pTrappedEnemy{ nullptr };

		void HandleHorizontalMovement();
		void HandleVerticalMovement();
	};
}
