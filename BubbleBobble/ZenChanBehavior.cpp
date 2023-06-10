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
		Component{ pOwner },
		m_pTransformComponent{ pOwner->AddComponent<TransformComponent>() },
		m_pRenderSpriteComponent{ pOwner->AddComponent<RenderSpriteComponent>() },
		m_pColliderComponent{ pOwner->AddComponent<ColliderComponent>() },
		m_pRigidbodyComponent{ pOwner->AddComponent<RigidbodyComponent>() }
	{
		m_pRigidbodyComponent->SetMaxVelocity({ m_Speed, m_JumpForce });

		Spawn();
	}

	void ZenChanBehavior::Update()
	{
		HandleState();
	}

	void ZenChanBehavior::SetSpeed(float speed)
	{
		m_Speed = speed;
		m_pRigidbodyComponent->SetMaxVelocity({ m_Speed, m_JumpForce });
	}

	void ZenChanBehavior::SetJumpForce(float jumpForce)
	{
		m_JumpForce = jumpForce;
		m_pRigidbodyComponent->SetMaxVelocity({ m_Speed, m_JumpForce });
	}

	void ZenChanBehavior::AddAnimation(const std::string& name, const SpriteAnimation& animation)
	{
		// No need to perform null checks, since the constructor already adds the components
		m_pRenderSpriteComponent->AddAnimation(name, animation);
		m_pColliderComponent->SetDimensions(m_pRenderSpriteComponent->GetFrameSize());
	}

	void ZenChanBehavior::HandleState()
	{
		const bool IsGrounded{ m_pRigidbodyComponent->IsGrounded() };

		if (IsGrounded)
		{
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
			m_pRenderSpriteComponent->SetAnimation("Bubble");
			break;
		case ZenChanState::Death:
			break;
		case ZenChanState::Walk:
			m_pRenderSpriteComponent->SetAnimation("Walk");
			break;
		}
	}

	void ZenChanBehavior::HandleMovement()
	{
		FindClosestTarget();
		SeekTarget();
	}

	void ZenChanBehavior::HandleSpriteFlip()
	{
		const auto& velocity{ m_pRigidbodyComponent->GetVelocity() };

		if (velocity.x > FLT_EPSILON)
		{
			m_pRenderSpriteComponent->SetFlipX(true);
		}
		else if (velocity.x < -FLT_EPSILON)
		{
			m_pRenderSpriteComponent->SetFlipX(false);
		}
	}

	void ZenChanBehavior::FindClosestTarget()
	{
		const auto& pos{ m_pTransformComponent->GetWorldPosition() };
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
		if (!m_pRigidbodyComponent->IsGrounded()) return;

		const auto& pos{ m_pTransformComponent->GetWorldPosition() };
		const float horizontalDistance{ pos.x - m_TargetPos.x };
		const float verticalDistance{ pos.y - m_TargetPos.y };

		const bool isVerticalThreshold{ std::fabs(verticalDistance) > m_JumpThreshold };

		// Check if we should change direction
		// if not, just keep moving in the same direction
		if (!isVerticalThreshold || !m_pRigidbodyComponent->IsMoving())
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

		m_pRigidbodyComponent->AddForce({ m_DirectionToTarget.x * m_Speed, .0f });
		if (m_DirectionToTarget.y > FLT_EPSILON)
		{
			m_pRigidbodyComponent->SetVelocity({ m_pRigidbodyComponent->GetVelocity().x, -m_JumpForce });
		}
	}

	void ZenChanBehavior::Spawn()
	{
		const auto& level{ GameManager::GetInstance().GetCurrentLevel() };
		if (!level) return;

		const float levelScale{ level->GetLevelScale() };

		// Subtract a quarter of the scale, so the player is centered
		const float scale{ levelScale - (levelScale / 4.f) };
		m_pTransformComponent->SetScale(scale); // Set the scale of the player based on the level scale

		//glm::vec2 spawnPos{ level->GetPlayerSpawnPosition(m_PlayerId) };
		//m_pTransformComponent->SetPosition(spawnPos);
		glm::vec2 spawnPos{ 200.f, 200.f };
		m_pTransformComponent->SetPosition(spawnPos);

		// If the players position is over the half of the screen, flip the sprite
		int width;
		int height;
		Renderer::GetInstance().GetWindowSize(width, height);

		if (spawnPos.x < static_cast<float>(width) * .5f)
		{
			m_pRenderSpriteComponent->SetFlipX(true);
		}
	}
}
