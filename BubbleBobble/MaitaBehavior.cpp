#include "MaitaBehavior.h"
#include "Renderer.h"
#include "TransformComponent.h"
#include "RenderSpriteComponent.h"
#include "RigidbodyComponent.h"
#include "GameManager.h"
#include <glm/glm.hpp>

namespace dae
{
	MaitaBehavior::MaitaBehavior(GameObject* pOwner) :
		EnemyBehavior{ pOwner }
	{
		Spawn(glm::vec2{ 200.f, 200.f });
	}

	void MaitaBehavior::Update()
	{
		HandleState();
	}

	void MaitaBehavior::EnterBubble()
	{
		SetState(MaitaState::Bubble);
		GetRigidbodyComponent()->EnableGravity(false);
	}

	void MaitaBehavior::ExitBubble()
	{
		SetState(MaitaState::Walk);
		GetRigidbodyComponent()->EnableGravity(true);
	}

	void MaitaBehavior::HandleState()
	{
		if (GetRigidbodyComponent()->IsGrounded())
		{
			SetState(MaitaState::Walk);
			HandleMovement();
		}

		HandleSpriteFlip();
	}

	void MaitaBehavior::SetState(MaitaState state)
	{
		if (m_State == state) return;

		m_State = state;

		switch (m_State)
		{
		case MaitaState::Bubble:
			GetRenderSpriteComponent()->SetAnimation("Bubble");
			break;
		case MaitaState::Death:
			break;
		case MaitaState::Walk:
			GetRenderSpriteComponent()->SetAnimation("Walk");
			break;
		}
	}

	void MaitaBehavior::HandleSpriteFlip()
	{
		const auto& velocity{ GetRigidbodyComponent()->GetVelocity() };

		if (velocity.x > FLT_EPSILON)
		{
			GetRenderSpriteComponent()->SetFlipX(true);
		}
		else if (velocity.x < -FLT_EPSILON)
		{
			GetRenderSpriteComponent()->SetFlipX(false);
		}
	}

	void MaitaBehavior::HandleMovement()
	{
		FindClosestTarget();
		SeekTarget();
	}
	void MaitaBehavior::FindClosestTarget()
	{
		const auto& pos{ GetTransformComponent()->GetWorldPosition() };
		const auto& targets{ GameManager::GetInstance().GetPlayers() };

		if (targets.empty())
		{
			m_TargetPos = pos;
			return;
		}

		float closestDistance{ FLT_MAX };
		for (const auto& target : targets)
		{
			const auto& targetPos{ target->GetPosition() };
			const float sqrDistance{ std::fabs((targetPos.x - pos.x) * (targetPos.x - pos.x) + (targetPos.y - pos.y) * (targetPos.y - pos.y)) };

			if (sqrDistance < closestDistance)
			{
				closestDistance = sqrDistance;
				m_TargetPos = targetPos;
			}
		}
	}

	void MaitaBehavior::SeekTarget()
	{
		if (!GetRigidbodyComponent()->IsGrounded()) return;

		const auto& pos{ GetTransformComponent()->GetWorldPosition() };
		const float horizontalDistance{ pos.x - m_TargetPos.x };
		const float verticalDistance{ pos.y - m_TargetPos.y };

		const bool isVerticalThreshold{ std::fabs(verticalDistance) > m_JumpThreshold };

		// Check if we should change direction
		// if not, just keep moving in the same direction
		if (!isVerticalThreshold || !GetRigidbodyComponent()->IsMoving())
		{
			m_DirectionToTarget.x = (m_TargetPos.x < pos.x) ? -1.f : 1.f;
		}

		// Can we jump?
		if (isVerticalThreshold && verticalDistance > FLT_EPSILON && std::fabs(horizontalDistance) < std::fabs(verticalDistance))
		{
			m_DirectionToTarget.y = 1.f;
		}
		else
		{
			m_DirectionToTarget.y = .0f;
		}

		GetRigidbodyComponent()->AddForce({ m_DirectionToTarget.x * GetSpeed(), .0f });
		if (m_DirectionToTarget.y > FLT_EPSILON)
		{
			GetRigidbodyComponent()->SetVelocity({ GetRigidbodyComponent()->GetVelocity().x, -GetJumpForce() });
		}
	}
}
