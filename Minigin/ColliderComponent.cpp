#include "ColliderComponent.h"
#include "CollisionSystem.h"
#include "GameObject.h"
#include <iostream>

namespace dae
{
	ColliderComponent::ColliderComponent(GameObject* pOwner) :
		Component{ pOwner },
		m_pCollisionEvent{ std::make_unique<CollisionEvent>() }
	{
		CollisionSystem::GetInstance().AddCollider(this);
	}

	ColliderComponent::~ColliderComponent()
	{
		CollisionSystem::GetInstance().RemoveCollider(this);
	}

	void ColliderComponent::Update()
	{
		for (const auto& pCollider : CollisionSystem::GetInstance().GetColliders())
		{
			if (pCollider == this)
				continue;

			glm::vec2 dir{ .0f, .0f };
			if (IsColliding(pCollider, dir))
			{
				m_pCollisionEvent->Notify(pCollider, this, dir);
			}
		}
	}

	bool ColliderComponent::IsColliding(const ColliderComponent* other, glm::vec2& dir) const
	{
		const auto& otherTransform{ other->GetOwner()->GetTransformComponent() };
		const auto& thisTransform{ GetOwner()->GetTransformComponent() };

		const auto& otherPos{ otherTransform->GetWorldPosition() };
		const auto& otherDim{ other->GetDimensions() * otherTransform->GetScale() };

		const auto& thisPos{ thisTransform->GetWorldPosition() };
		const auto& thisDim{ GetDimensions() * thisTransform->GetScale() };

		if (otherPos.x + otherDim.x >= thisPos.x &&
			otherPos.x <= thisPos.x + thisDim.x &&
			otherPos.y + otherDim.y >= thisPos.y &&
			otherPos.y <= thisPos.y + thisDim.y)
		{
			const auto overlapX{ std::min(otherPos.x + otherDim.x - thisPos.x, thisPos.x + thisDim.x - otherPos.x) };
			const auto overlapY{ std::min(otherPos.y + otherDim.y - thisPos.y, thisPos.y + thisDim.y - otherPos.y) };

			if (overlapX < overlapY)
			{
				dir.x = otherPos.x > thisPos.x ? 1.f : -1.f;
			}
			else
			{
				dir.y = otherPos.y > thisPos.y ? 1.f : -1.f;
			}

			return true;
		}

		return false;
	}
}
