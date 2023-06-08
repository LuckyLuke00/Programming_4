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
		//for (const auto& pCollider : CollisionSystem::GetInstance().GetColliders())
		//{
		//	if (pCollider == this)
		//		continue;

		//	glm::vec2 dir{ .0f, .0f };
		//	if (IsColliding(pCollider, dir))
		//	{
		//		m_pCollisionEvent->Notify(pCollider, this, dir);
		//	}
		//}
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
			const auto overlapX{ std::min(otherPos.x - otherDim.x + thisPos.x, thisPos.x - thisDim.x + otherPos.x) };
			const auto overlapY{ std::min(otherPos.y + otherDim.y - thisPos.y, thisPos.y + thisDim.y - otherPos.y) };

			dir = glm::vec2{ overlapX, overlapY };

			//if (overlapX < overlapY)
			//{
			//	dir.x = overlapX;
			//}
			//else
			//{
			//	dir.y = overlapY;
			//}

			//if (other->GetColliderType() == ColliderType::OneWay)
			//{
			//	if (thisPos.y > otherPos.y)
			//	{
			//		return false;
			//	}
			//}

			return true;
		}

		return false;
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

			if (otherPos.x + otherDim.x > thisPos.x &&
				otherPos.x < thisPos.x + thisDim.x &&
				otherPos.y + otherDim.y > thisPos.y &&
				otherPos.y < thisPos.y + thisDim.y)
			{
				const float leftX{ -otherPos.x + thisPos.x + thisDim.x };
				const float rightX{ thisPos.x - otherDim.x - otherPos.x };
				const float overlapX{ std::fabsf(leftX) < std::fabsf(rightX) ? leftX : rightX };

				const float leftY{ -otherPos.y + thisPos.y + thisDim.y };
				const float rightY{ thisPos.y - otherDim.y - otherPos.y };
				const float overlapY{ std::fabsf(leftY) < std::fabsf(rightY) ? leftY : rightY };

				dir = glm::vec2{ overlapX, overlapY };

				if (pCollider->GetColliderType() == ColliderType::OneWay)
				{
					if (overlapY < .0f)
					{
						return false; // Ignore the collision
					}
				}

				return true;
			}
		}

		return false;
	}
}
