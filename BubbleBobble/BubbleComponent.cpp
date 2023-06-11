#include "BubbleComponent.h"
#include "GameObject.h"
#include "RenderSpriteComponent.h"
#include "ColliderComponent.h"
#include "GameManager.h"
#include "Timer.h"
#include "SceneManager.h"
#include "Scene.h"
#include "EnemyBehavior.h"

#include <iostream>
namespace dae
{
	BubbleComponent::BubbleComponent(GameObject* pOwner) :
		Component{ pOwner },
		m_pTransformComponent{ pOwner->AddComponent<TransformComponent>() },
		m_pRenderSpriteComponent{ pOwner->AddComponent<RenderSpriteComponent>() },
		m_pColliderComponent{ pOwner->AddComponent<ColliderComponent>() }
	{
		const auto& level{ GameManager::GetInstance().GetCurrentLevel() };
		if (!level) return;

		const float levelScale{ level->GetLevelScale() };

		// Subtract a quarter of the scale, so the player is centered
		const float scale{ levelScale - (levelScale / 4.f) };
		m_pTransformComponent->SetScale(scale); // Set the scale of the player based on the level scale

		m_pColliderComponent->SetIsTrigger(true);
		m_pColliderComponent->SetTriggerCallback(std::bind_front(&BubbleComponent::OnTrigger, this));
	}

	void BubbleComponent::Update()
	{
		if (!m_IsBlowing) return;

		if (m_pTrappedEnemy && m_pTrappedEnemy->IsDead())
		{
			PopBubble();
			return;
		}

		// Move the bubble
		const float dt{ Timer::GetDeltaSeconds() };
		m_pTransformComponent->Translate(m_Velocity * dt);
		if (m_pTrappedEnemy) m_pTrappedEnemy->GetTransformComponent()->SetPosition(m_pTransformComponent->GetWorldPosition());

		HandleHorizontalMovement();
		HandleVerticalMovement();
	}

	void BubbleComponent::AddAnimation(const std::string& name, const SpriteAnimation& animation)
	{
		m_pRenderSpriteComponent->AddAnimation(name, animation);
		m_pColliderComponent->SetDimensions(m_pRenderSpriteComponent->GetFrameSize());
	}

	void BubbleComponent::BlowBubble(int direction)
	{
		m_IsBlowing = true;

		// Store a -1 or 1 based on the direction
		m_Direction = (direction < 0) ? -1.f : 1.f;

		// Set the velocity of the bubble
		m_Velocity.x = m_Direction * m_InitialVelocity;
		m_Velocity.y = 0;
	}

	void BubbleComponent::OnTrigger(const GameObject* other)
	{
		if (!other) return;
		if (m_pTrappedEnemy) return;
		if (other->GetTag() != "Enemy") return;

		// Other, contains an inherited class of EnemyBehavior, we need to get the EnemyBehavior component
		m_pTrappedEnemy = other->GetComponent<EnemyBehavior>();
		if (m_pTrappedEnemy)
		{
			m_pRenderSpriteComponent->SetEnabled(false);
			m_pTrappedEnemy->EnterBubble();
		}
	}

	void BubbleComponent::PopBubble()
	{
		GetOwner()->MarkForDelete();

		if (!m_pTrappedEnemy) return;
		if (!m_pTrappedEnemy->IsDead()) m_pTrappedEnemy->ExitBubble();
		m_pTrappedEnemy = nullptr;
	}

	void BubbleComponent::HandleHorizontalMovement()
	{
		const float dt{ Timer::GetDeltaSeconds() };

		if (m_Velocity.x * m_Direction > FLT_EPSILON)
		{
			// Slow down the bubble
			m_Velocity.x -= m_Direction * m_Deceleration * dt;
		}
		else
		{
			m_Velocity.x = .0f;
		}
	}

	void BubbleComponent::HandleVerticalMovement()
	{
		if (std::fabs(m_Velocity.x) > FLT_EPSILON) return;

		if (m_pTransformComponent->GetWorldPosition().y > m_MaxYPos)
		{
			m_Velocity.y = -m_RiseSpeed;
		}
		else
		{
			m_Velocity.y = .0f;
		}

		m_BubbleTimer += Timer::GetDeltaSeconds();
		if (m_BubbleTimer >= m_BubbleTime)
		{
			PopBubble();
		}
	}
}
