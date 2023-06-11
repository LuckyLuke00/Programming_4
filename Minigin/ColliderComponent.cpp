#include "ColliderComponent.h"
#include "CollisionSystem.h"
#include "GameObject.h"
#include <iostream>

namespace dae
{
	ColliderComponent::ColliderComponent(GameObject* pOwner) :
		Component{ pOwner }
	{
		CollisionSystem::GetInstance().AddCollider(this);
	}

	ColliderComponent::~ColliderComponent()
	{
		CollisionSystem::GetInstance().RemoveCollider(this);
	}

	bool ColliderComponent::IsColliding(glm::vec2& dir) const
	{
		for (const auto& pCollider : CollisionSystem::GetInstance().GetColliders())
		{
			if (pCollider == this)
				continue;

			const auto& otherTransform{ pCollider->GetOwner()->GetTransformComponent() };
			const auto& thisTransform{ GetOwner()->GetTransformComponent() };

			const auto& otherPos{ otherTransform->GetWorldPosition() };
			const auto& otherDim{ pCollider->GetDimensions() * otherTransform->GetScale() };

			const auto& thisPos{ thisTransform->GetWorldPosition() };
			const auto& thisDim{ GetDimensions() * thisTransform->GetScale() };

			if (!CheckCollision(thisPos, thisDim, otherPos, otherDim)) continue;

			if (pCollider->IsTrigger()) // Trigger
			{
				HandleTriggerCollision(pCollider);
				return false;
			}

			CalculateOverlap(thisPos, thisDim, otherPos, otherDim, dir);

			// One way collision, ignore if the other collider is below this one
			if (pCollider->GetColliderType() == ColliderType::OneWay && dir.y < .0f)
			{
				return false;
			}

			return true;
		}

		return false;
	}

	bool ColliderComponent::CheckCollision(const glm::vec2& posA, const glm::vec2& dimA, const glm::vec2& posB, const glm::vec2& dimB) const
	{
		return posB.x + dimB.x > posA.x &&
			posB.x < posA.x + dimA.x &&
			posB.y + dimB.y > posA.y &&
			posB.y < posA.y + dimA.y;
	}

	void ColliderComponent::HandleTriggerCollision(const ColliderComponent* pOther) const
	{
		const auto& pTriggerCallback{ pOther->GetTriggerCallback() };
		if (pTriggerCallback) pTriggerCallback(GetOwner());
	}

	void ColliderComponent::CalculateOverlap(const glm::vec2& posA, const glm::vec2& dimA, const glm::vec2& posB, const glm::vec2& dimB, glm::vec2& dir) const
	{
		const float leftX = -posB.x + posA.x + dimA.x;
		const float rightX = posA.x - dimB.x - posB.x;
		const float overlapX = std::fabsf(leftX) < std::fabsf(rightX) ? leftX : rightX;

		const float leftY = -posB.y + posA.y + dimA.y;
		const float rightY = posA.y - dimB.y - posB.y;
		const float overlapY = std::fabsf(leftY) < std::fabsf(rightY) ? leftY : rightY;

		dir = glm::vec2{ overlapX, overlapY };
	}
}
