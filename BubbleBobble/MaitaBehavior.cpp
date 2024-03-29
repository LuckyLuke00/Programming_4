#include "MaitaBehavior.h"
#include "ColliderComponent.h"
#include "GameManager.h"
#include "RenderSpriteComponent.h"
#include "RigidbodyComponent.h"
#include "PickupComponent.h"
#include "GameObject.h"
#include "Scene.h"
#include "BoulderComponent.h"
#include "Timer.h"
#include "SoundSystem.h"
#include "SoundIds.h"

namespace dae
{
	MaitaBehavior::MaitaBehavior(GameObject* pOwner) :
		EnemyBehavior{ pOwner }
	{
	}

	void MaitaBehavior::Update()
	{
		HandleState();
		WrapAroundScreen();
	}

	void MaitaBehavior::EnterBubble()
	{
		if (m_State == MaitaState::Bubble) return;

		SetState(MaitaState::Bubble);
		GetRigidbodyComponent()->EnableGravity(false);
		GetColliderComponent()->SetIsTrigger(true);
	}

	void MaitaBehavior::ExitBubble()
	{
		if (IsDead()) return;

		SetState(MaitaState::Walk);
		GetRigidbodyComponent()->EnableGravity(true);
		GetColliderComponent()->SetIsTrigger(false);
	}

	void MaitaBehavior::Kill()
	{
		SetState(MaitaState::Death);

		// Play the death sound
		ServiceLocator<SoundSystem>::GetService().PlaySound(static_cast<unsigned short>(SoundIds::Death), .5f);
	}

	void MaitaBehavior::SpawnOnDeath() const
	{
		auto fries{ std::make_shared<dae::GameObject>() };
		auto pickup{ fries->AddComponent<PickupComponent>() };

		pickup->SetPickupType(PickupType::Fries);
		pickup->SetPosition(GetTransformComponent()->GetWorldPosition());
		pickup->SetTexture("Sprites/Enemies/Maita/maita_pickup.png");

		SceneManager::GetInstance().GetActiveScene()->Add(fries);
	}

	void MaitaBehavior::HandleState()
	{
		if (m_State == MaitaState::Bubble) return;
		if (GetRigidbodyComponent()->IsGrounded())
		{
			if (IsDead())
			{
				SpawnOnDeath();
				GetOwner()->MarkForDelete();
				GameManager::GetInstance().RemoveEnemy(GetOwner());
				return;
			}
			SetState(MaitaState::Walk);
			HandleMovement();
		}

		HandleSpriteFlip();

		m_BoulderCooldownTimer += Timer::GetDeltaSeconds();
		if (m_BoulderCooldownTimer >= m_BoulderCooldownTime)
		{
			ThrowBoulder();
			m_BoulderCooldownTimer = .0f;
		}
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
			GetRenderSpriteComponent()->SetAnimation("Death");
			break;
		case MaitaState::Walk:
			GetRenderSpriteComponent()->SetAnimation("Walk");
			break;
		}
	}

	void MaitaBehavior::HandleSpriteFlip() const
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
			if (target->IsDead()) continue;

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
		if (!GetRigidbodyComponent()->IsMoving())
		{
			// Choose a random direction
			m_DirectionToTarget.x = (rand() % 2 == 0) ? -1.f : 1.f;
		}
		else if (!isVerticalThreshold)
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

	void MaitaBehavior::ThrowBoulder() const
	{
		auto boulder{ std::make_shared<GameObject>() };
		auto boulderComponent{ boulder->AddComponent<BoulderComponent>() };

		// Set the position of the bubble to the player
		const auto& pos{ GetTransformComponent()->GetWorldPosition() };
		boulder->GetTransformComponent()->SetPosition(pos);

		// Animation
		dae::SpriteAnimation boulderAnim;
		boulderAnim.rows = 1;
		boulderAnim.cols = 4;
		boulderAnim.fps = 6;
		boulderAnim.frames = 4;

		boulderAnim.SetTexture("Sprites/Enemies/Maita/maita_boulder.png");

		boulderComponent->AddAnimation("Boulder", boulderAnim);

		// Set the texture of the bubble
		SceneManager::GetInstance().GetActiveScene()->Add(boulder);
		boulderComponent->ThrowBoulder(GetRenderSpriteComponent()->GetFlipX() ? 1 : -1);
	}
}
