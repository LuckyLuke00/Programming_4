#include "RigidbodyComponent.h"
#include "CollisionEvent.h"
#include "GameObject.h"
#include "ColliderComponent.h"
#include "Timer.h"
#include <iostream>

namespace dae
{
	RigidbodyComponent::RigidbodyComponent(GameObject* pOwner) :
		Component{ pOwner },
		m_pColliderComponent{ pOwner->GetComponent<ColliderComponent>() },
		m_pTransformComponent{ pOwner->GetTransformComponent() }
	{}

	void RigidbodyComponent::Update()
	{
		const float dt{ Timer::GetDeltaSeconds() };
		if (m_GravityEnabled && m_Velocity.y < m_MaxVelocity.y) m_Velocity.y += m_Gravity * dt;

		// Apply friction
		if (m_FrictionEnabled) ApplyFriction();
		m_IsGrounded = false;

		// Apply vertical movement
		m_pTransformComponent->Translate(.0f, m_Velocity.y * dt);

		// Check for vertical collisions
		glm::vec2 verticalCollisionDir{};
		if (m_pColliderComponent->IsColliding(verticalCollisionDir))
		{
			if (verticalCollisionDir.y > .0f)
			{
				m_IsGrounded = true;
				if (m_pColliderComponent->IsTrigger()) return; // We still want ground detection for triggers

				// Collision from below
				m_pTransformComponent->Translate(.0f, -verticalCollisionDir.y);
				m_Velocity.y = .0f;
			}
			else if (!m_pColliderComponent->IsTrigger() && verticalCollisionDir.y < .0f)
			{
				// Collision from above
				m_pTransformComponent->Translate(.0f, -verticalCollisionDir.y);
				m_Velocity.y = .0f;
			}
		}

		// Apply horizontal movement
		m_pTransformComponent->Translate(m_Velocity.x * dt, .0f);

		// Check for horizontal collisions
		glm::vec2 horizontalCollisionDir{};
		if (m_pColliderComponent->IsColliding(horizontalCollisionDir))
		{
			if (m_pColliderComponent->IsTrigger()) return;
			if (horizontalCollisionDir.x > .0f || horizontalCollisionDir.x < .0f)
			{
				// Collision from the right
				m_pTransformComponent->Translate(-horizontalCollisionDir.x, .0f);
				m_Velocity.x = .0f;
			}
		}
	}

	void RigidbodyComponent::AddForce(const glm::vec2& force)
	{
		// Add force to velocity, but don't exceed max velocity
		m_Velocity += force;
		m_Velocity.x = std::clamp(m_Velocity.x, -m_MaxVelocity.x, m_MaxVelocity.x);
		m_Velocity.y = std::clamp(m_Velocity.y, -m_MaxVelocity.y, m_MaxVelocity.y);
	}

	void RigidbodyComponent::ApplyFriction()
	{
		const float dt{ Timer::GetDeltaSeconds() };

		if (m_Velocity.x > .0f)
		{
			m_Velocity.x -= m_Friction * dt;
			if (m_Velocity.x < .0f) m_Velocity.x = .0f;
		}
		else if (m_Velocity.x < .0f)
		{
			m_Velocity.x += m_Friction * dt;
			if (m_Velocity.x > .0f) m_Velocity.x = .0f;
		}
	}
}
