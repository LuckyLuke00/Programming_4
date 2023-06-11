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
		m_pRigidbodyComponent->SetMaxVelocity({ m_Speed, m_JumpForce });
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
}
