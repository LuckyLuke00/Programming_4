#pragma once
#include "Component.h"
#include <string>
#include <glm/glm.hpp>

namespace dae
{
	class ColliderComponent;
	class RenderSpriteComponent;
	class RigidbodyComponent;
	class TransformComponent;
	struct SpriteAnimation;

	enum class ZenChanState
	{
		Bubble,
		Death,
		Walk
	};

	class ZenChanBehavior final : public Component
	{
	public:
		explicit ZenChanBehavior(GameObject* pOwner);
		~ZenChanBehavior() override = default;

		ZenChanBehavior(const ZenChanBehavior& other) = delete;
		ZenChanBehavior(ZenChanBehavior&& other) noexcept = delete;
		ZenChanBehavior& operator=(const ZenChanBehavior& other) = delete;
		ZenChanBehavior& operator=(ZenChanBehavior&& other) noexcept = delete;

		void Update() override;

		void SetSpeed(float speed);
		void SetJumpForce(float jumpForce);

		void AddAnimation(const std::string& name, const SpriteAnimation& animation);
	private:
		ZenChanState m_State{ -1 };

		TransformComponent* m_pTransformComponent{ nullptr };
		RenderSpriteComponent* m_pRenderSpriteComponent{ nullptr };
		ColliderComponent* m_pColliderComponent{ nullptr };
		RigidbodyComponent* m_pRigidbodyComponent{ nullptr };

		glm::vec2 m_TargetPos{};
		glm::vec2 m_DirectionToTarget{};

		float m_Speed{ 50.f };
		float m_JumpForce{ 130.f };

		float m_JumpThreshold{ 50.f };

		void HandleState();
		void SetState(ZenChanState state);
		void HandleMovement();
		void HandleSpriteFlip();
		void FindClosestTarget();
		void SeekTarget();
		void Spawn();
	};
}
