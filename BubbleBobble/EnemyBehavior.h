#pragma once
#include <string>
#include "Component.h"
#include <glm/glm.hpp>

namespace dae
{
	class TransformComponent;
	class RenderSpriteComponent;
	class ColliderComponent;
	class RigidbodyComponent;
	struct SpriteAnimation;

	class EnemyBehavior : public Component
	{
	public:
		explicit EnemyBehavior(GameObject* pOwner);
		~EnemyBehavior() override = default;

		EnemyBehavior(const EnemyBehavior& other) = delete;
		EnemyBehavior(EnemyBehavior&& other) noexcept = delete;
		EnemyBehavior& operator=(const EnemyBehavior& other) = delete;
		EnemyBehavior& operator=(EnemyBehavior&& other) noexcept = delete;

		void AddAnimation(const std::string& name, const SpriteAnimation& animation);

		void SetSpeed(float speed);
		void SetJumpForce(float jumpForce);

		float GetSpeed() const { return m_Speed; }
		float GetJumpForce() const { return m_JumpForce; }

		virtual void EnterBubble() = 0;
		virtual void ExitBubble() = 0;

		TransformComponent* GetTransformComponent() const { return m_pTransformComponent; }
		RenderSpriteComponent* GetRenderSpriteComponent() const { return m_pRenderSpriteComponent; }
		ColliderComponent* GetColliderComponent() const { return m_pColliderComponent; }
		RigidbodyComponent* GetRigidbodyComponent() const { return m_pRigidbodyComponent; }

	protected:
		void Spawn(const glm::vec2& spawnPos) const;

	private:
		float m_Speed{ 50.f };
		float m_JumpForce{ 130.f };

		TransformComponent* m_pTransformComponent{ nullptr };
		RenderSpriteComponent* m_pRenderSpriteComponent{ nullptr };
		ColliderComponent* m_pColliderComponent{ nullptr };
		RigidbodyComponent* m_pRigidbodyComponent{ nullptr };

		void ScaleToLevelSize();
	};
}
