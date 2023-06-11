#include "EnemyBehavior.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "RenderSpriteComponent.h"
#include "ColliderComponent.h"
#include "RigidbodyComponent.h"
#include "GameManager.h"
#include "Renderer.h"

namespace dae
{
	EnemyBehavior::EnemyBehavior(GameObject* pOwner) :
		Component{ pOwner },
		m_pTransformComponent{ pOwner->AddComponent<TransformComponent>() },
		m_pRenderSpriteComponent{ pOwner->AddComponent<RenderSpriteComponent>() },
		m_pColliderComponent{ pOwner->AddComponent<ColliderComponent>() },
		m_pRigidbodyComponent{ pOwner->AddComponent<RigidbodyComponent>() }
	{
		pOwner->SetTag("Enemy");
		m_pRigidbodyComponent->SetMaxVelocity({ m_Speed, m_JumpForce });
		m_pColliderComponent->SetTriggerCallback(std::bind_front(&EnemyBehavior::OnTrigger, this));
		ScaleToLevelSize();
	}

	void EnemyBehavior::AddAnimation(const std::string& name, const SpriteAnimation& animation)
	{
		m_pRenderSpriteComponent->AddAnimation(name, animation);
		m_pColliderComponent->SetDimensions(m_pRenderSpriteComponent->GetFrameSize());
	}

	void EnemyBehavior::SetSpeed(float speed)
	{
		m_Speed = speed;
		m_pRigidbodyComponent->SetMaxVelocity({ m_Speed, m_JumpForce });
	}

	void EnemyBehavior::SetJumpForce(float jumpForce)
	{
		m_JumpForce = jumpForce;
		m_pRigidbodyComponent->SetMaxVelocity({ m_Speed, m_JumpForce });
	}

	void EnemyBehavior::Spawn(const glm::vec2& spawnPos) const
	{
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

	void EnemyBehavior::ScaleToLevelSize()
	{
		const auto& level{ GameManager::GetInstance().GetCurrentLevel() };
		if (!level) return;

		const float levelScale{ level->GetLevelScale() };

		// Subtract a quarter of the scale, so the player is centered
		const float scale{ levelScale - (levelScale / 4.f) };
		m_pTransformComponent->SetScale(scale); // Set the scale of the player based on the level scale
	}

	void EnemyBehavior::OnTrigger(const GameObject* other)
	{
		if (IsDead()) return; // Prevents the enemy from dying multiple times
		if (!other || other->GetTag() != "Player") return;

		m_pColliderComponent->AddIgnoreTag("Player");
		m_pColliderComponent->AddIgnoreTag("Enemy");

		if (const auto rb{ other->GetComponent<RigidbodyComponent>() })
		{
			// Launch in the opposite direction of the player
			const auto& vel{ rb->GetVelocity() };
			m_pRigidbodyComponent->SetVelocity({ GetJumpForce() * .75f * ((vel.x > .0f) ? 1.f : -1.f), -GetJumpForce() * .75f });
		}

		m_pRigidbodyComponent->EnableGravity(true);
		m_pRigidbodyComponent->EnableFriction(false);
		m_pColliderComponent->SetIsTrigger(false);

		Kill();
	}

	void EnemyBehavior::WrapAroundScreen()
	{
		int width;
		int height;
		Renderer::GetInstance().GetWindowSize(width, height);

		// Check if the player is out of the screen
		const auto& pos{ m_pTransformComponent->GetWorldPosition() };
		const glm::vec2& frameSize{ m_pRenderSpriteComponent->GetFrameSize() };

		if (pos.y > static_cast<float>(height))
		{
			m_pTransformComponent->SetPosition(pos.x, .0f - frameSize.y);
		}

		if (pos.x > static_cast<float>(width))
		{
			m_pTransformComponent->SetPosition(.0f - frameSize.x, pos.y);
		}
		else if (pos.x < .0f - frameSize.x)
		{
			m_pTransformComponent->SetPosition(static_cast<float>(width), pos.y);
		}
	}
}
