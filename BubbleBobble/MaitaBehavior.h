#pragma once
#include "EnemyBehavior.h"

namespace dae
{
	enum class MaitaState
	{
		Attack,
		Bubble,
		Death,
		Walk
	};

	class MaitaBehavior final : public EnemyBehavior
	{
	public:
		explicit MaitaBehavior(GameObject* pOwner);
		~MaitaBehavior() override = default;

		MaitaBehavior(const MaitaBehavior& other) = delete;
		MaitaBehavior(MaitaBehavior&& other) noexcept = delete;
		MaitaBehavior& operator=(const MaitaBehavior& other) = delete;
		MaitaBehavior& operator=(MaitaBehavior&& other) noexcept = delete;

		void Update() override;

		bool IsDead() const override { return m_State == MaitaState::Death; }
		void EnterBubble() override;
		void ExitBubble() override;
		void Kill() override;
		void SpawnOnDeath() const override;

	private:
		MaitaState m_State{ -1 };

		float m_JumpThreshold{ 50.f };
		float m_BoulderCooldownTime{ 5.f };
		float m_BoulderCooldownTimer{ .0f };

		glm::vec2 m_DirectionToTarget{ .0f, .0f };
		glm::vec2 m_TargetPos{ .0f, .0f };

		void HandleState();
		void SetState(MaitaState state);

		void HandleSpriteFlip() const;

		// Movement
		void HandleMovement();
		void FindClosestTarget();
		void SeekTarget();

		void ThrowBoulder() const;
	};
}
