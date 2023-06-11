#pragma once
#include "EnemyBehavior.h"

namespace dae
{
	enum class MaitaState
	{
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

		void EnterBubble() override;
		void ExitBubble() override;

	private:
		MaitaState m_State{ -1 };

		float m_JumpThreshold{ 50.f };

		glm::vec2 m_DirectionToTarget{ .0f, .0f };
		glm::vec2 m_TargetPos{ .0f, .0f };

		void HandleState();
		void SetState(MaitaState state);

		void HandleSpriteFlip();

		// Movement
		void HandleMovement();
		void FindClosestTarget();
		void SeekTarget();
	};
}
