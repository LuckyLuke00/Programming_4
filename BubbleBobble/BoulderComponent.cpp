#include "BoulderComponent.h"
#include "GameObject.h"
#include "RenderSpriteComponent.h"
#include "ColliderComponent.h"
#include "GameManager.h"
#include "Timer.h"
#include "Renderer.h"

namespace dae
{
	BoulderComponent::BoulderComponent(GameObject* pOwner) :
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
		m_pColliderComponent->SetTriggerCallback(std::bind_front(&BoulderComponent::OnTrigger, this));

		m_pColliderComponent->AddIgnoreTag("Enemy");

		m_Velocity.x = m_InitialVelocity;
	}

	void BoulderComponent::Update()
	{
		const float dt{ Timer::GetDeltaSeconds() };
		m_pTransformComponent->Translate(m_Velocity * dt);

		// Check if the bubble is out of bounds
		const float xPos{ m_pTransformComponent->GetWorldPosition().x };
		if (xPos > m_MaxXPos || xPos < m_MinXPos)
		{
			m_Velocity.x = .0f;
			GetOwner()->MarkForDelete();
			return;
		}
	}

	void BoulderComponent::AddAnimation(const std::string& name, const SpriteAnimation& animation)
	{
		m_pRenderSpriteComponent->AddAnimation(name, animation);
		m_pColliderComponent->SetDimensions(m_pRenderSpriteComponent->GetFrameSize());
	}

	void BoulderComponent::ThrowBoulder(int direction)
	{
		CalculateBounds();

		// Store a -1 or 1 based on the direction
		m_Direction = (direction < 0) ? -1.f : 1.f;

		// Set the velocity of the bubble
		m_Velocity.x = m_Direction * m_InitialVelocity;
		m_Velocity.y = 0;
	}

	void BoulderComponent::OnTrigger(const GameObject* other)
	{
		if (!other) return;
		if (other->GetTag() != "Player") return;

		m_pHitPlayer = other->GetComponent<PlayerComponent>();
		if (!m_pHitPlayer) return;

		m_pHitPlayer->Kill();
	}

	void BoulderComponent::CalculateBounds()
	{
		int width;
		int height;

		Renderer::GetInstance().GetWindowSize(width, height);

		const auto& level{ GameManager::GetInstance().GetCurrentLevel() };
		if (!level) return;

		const float levelScale{ level->GetLevelScale() };

		// Subtract a quarter of the scale, so the player is centered
		m_MinXPos = (m_LevelMargin * levelScale);
		m_MaxXPos = static_cast<float>(width) - m_MinXPos - (m_pRenderSpriteComponent->GetFrameSize().x * levelScale);
	}
}
