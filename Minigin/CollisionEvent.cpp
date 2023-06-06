#include "CollisionEvent.h"

void dae::CollisionEvent::Notify(ColliderComponent* pOtherCollider, ColliderComponent* pThisCollider, const glm::vec2& dir)
{
	m_pOtherCollider = pOtherCollider;
	m_pThisCollider = pThisCollider;

	m_CollisionDirection = dir;

	Subject<CollisionEvent>::Notify(*this);
}
