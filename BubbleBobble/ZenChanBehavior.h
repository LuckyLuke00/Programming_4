#pragma once
#include "EnemyBehavior.h"

namespace dae
{
	enum class ZenChanState
	{
		Bubble,
		Death,
		Walk
	};

	class ZenChanBehavior final : public EnemyBehavior
	{
	public:
		explicit ZenChanBehavior(GameObject* pOwner);
		~ZenChanBehavior() override = default;

		ZenChanBehavior(const ZenChanBehavior& other) = delete;
		ZenChanBehavior(ZenChanBehavior&& other) noexcept = delete;
		ZenChanBehavior& operator=(const ZenChanBehavior& other) = delete;
		ZenChanBehavior& operator=(ZenChanBehavior&& other) noexcept = delete;

		void Update() override;

		bool IsDead() const override { return m_State == ZenChanState::Death; }
		void EnterBubble() override;
		void ExitBubble() override;
		void Kill() override;
		void SpawnOnDeath() const override;

	private:
		ZenChanState m_State{ -1 };

		float m_JumpThreshold{ 50.f };

		glm::vec2 m_DirectionToTarget{ .0f, .0f };
		glm::vec2 m_TargetPos{ .0f, .0f };

		void HandleState();
		void SetState(ZenChanState state);

		void HandleSpriteFlip() const;

		// Movement
		void HandleMovement();
		void FindClosestTarget();
		void SeekTarget();
	};
}
