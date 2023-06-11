#include "ZenChanBehavior.h"
#include "ColliderComponent.h"
#include "RenderSpriteComponent.h"
#include "RigidbodyComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "GameManager.h"
#include "Renderer.h"

namespace dae
{
	ZenChanBehavior::ZenChanBehavior(GameObject* pOwner) :
		EnemyBehavior{ pOwner }
	{
		Spawn(glm::vec2{ 200.f, 200.f });
	}

	void ZenChanBehavior::Update()
	{
		HandleState();
	}

	void ZenChanBehavior::EnterBubble()
	{
		SetState(ZenChanState::Bubble);
		GetRigidbodyComponent()->EnableGravity(false);
		GetColliderComponent()->SetIsTrigger(true);
	}

	void ZenChanBehavior::ExitBubble()
	{
		if (IsDead()) return;

		SetState(ZenChanState::Walk);
		GetRigidbodyComponent()->EnableGravity(true);
		GetColliderComponent()->SetIsTrigger(false);
	}

	void ZenChanBehavior::Kill()
	{
		SetState(ZenChanState::Death);
	}

	void ZenChanBehavior::HandleState()
	{
		if (m_State == ZenChanState::Bubble) return;
		if (GetRigidbodyComponent()->IsGrounded())
		{
			if (IsDead())
			{
				GetOwner()->MarkForDelete();
				return;
			}
			SetState(ZenChanState::Walk);
			HandleMovement();
		}

		HandleSpriteFlip();
	}

	void ZenChanBehavior::SetState(ZenChanState state)
	{
		if (m_State == state) return;

		m_State = state;

		switch (m_State)
		{
		case ZenChanState::Bubble:
			GetRenderSpriteComponent()->SetAnimation("Bubble");
			break;
		case ZenChanState::Death:
			GetRenderSpriteComponent()->SetAnimation("Death");
			break;
		case ZenChanState::Walk:
			GetRenderSpriteComponent()->SetAnimation("Walk");
			break;
		}
	}

	void ZenChanBehavior::HandleSpriteFlip() const
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

	void ZenChanBehavior::HandleMovement()
	{
		FindClosestTarget();
		SeekTarget();
	}
	void ZenChanBehavior::FindClosestTarget()
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

	void ZenChanBehavior::SeekTarget()
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
