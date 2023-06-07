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
		m_pCollisionEvent{ pOwner->GetComponent<ColliderComponent>()->GetCollisionEvent() },
		m_pTransformComponent{ pOwner->GetTransformComponent() }
	{
		if (m_pCollisionEvent) m_pCollisionEvent->AddObserver(this);
		else std::cout << "RigidbodyComponent::RigidbodyComponent: No collision event found!\n";
	}

	RigidbodyComponent::~RigidbodyComponent()
	{
		if (m_pCollisionEvent) m_pCollisionEvent->RemoveObserver(this);
	}

	void RigidbodyComponent::Update()
	{
		m_IsGrounded = false;

		const float dt{ Timer::GetDeltaSeconds() };
		m_Velocity.y += m_Gravity * dt;

		m_pTransformComponent->Translate(m_Velocity * dt);

		// Apply drag
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

	void RigidbodyComponent::OnNotify(CollisionEvent event)
	{
		m_IsGrounded = false;

		if (event.GetCollisionDirection().x > .0f)
		{
			m_Velocity.x = .0f;
		}
		else if (event.GetCollisionDirection().x < .0f)
		{
			m_Velocity.x = .0f;
		}
		else if (event.GetCollisionDirection().y > .0f)
		{
			m_IsGrounded = true;
			m_Velocity.y = .0f;
		}
		else if (event.GetCollisionDirection().y < .0f)
		{
			m_Velocity.y = .0f;
		}

		// Translate the object out of the collision
		m_pTransformComponent->Translate(-event.GetCollisionDirection());
	}

	void RigidbodyComponent::AddForce(const glm::vec2& force)
	{
		// Add force to velocity, but don't exceed max velocity
		m_Velocity += force;
		m_Velocity.x = std::clamp(m_Velocity.x, -m_MaxVelocity.x, m_MaxVelocity.x);
		m_Velocity.y = std::clamp(m_Velocity.y, -m_MaxVelocity.y, m_MaxVelocity.y);
	}
}
