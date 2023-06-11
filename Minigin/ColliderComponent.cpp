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
		bool isColliding{ false }; // Wait until the end to return, so we can check for triggers first
		bool isOneWay{ false };
		bool isTrigger{ false };

		const ColliderComponent* pCollidedWith{ nullptr };

		for (const auto& pCollider : CollisionSystem::GetInstance().GetColliders())
		{
			if (pCollider == this)
				continue;

			// Check if the other collider is in the ignore list, or if this collider is in the other collider's ignore list
			if (std::ranges::find(pCollider->GetIgnoreTags(), GetOwner()->GetTag()) != pCollider->GetIgnoreTags().end())
			{
				continue;
			}

			if (std::ranges::find(m_IgnoreTags, pCollider->GetOwner()->GetTag()) != m_IgnoreTags.end())
			{
				continue;
			}

			const auto& otherTransform{ pCollider->GetOwner()->GetTransformComponent() };
			const auto& thisTransform{ GetOwner()->GetTransformComponent() };

			const auto& otherPos{ otherTransform->GetWorldPosition() };
			const auto& otherDim{ pCollider->GetDimensions() * otherTransform->GetScale() };

			const auto& thisPos{ thisTransform->GetWorldPosition() };
			const auto& thisDim{ GetDimensions() * thisTransform->GetScale() };

			if (!CheckCollision(thisPos, thisDim, otherPos, otherDim)) continue;

			pCollidedWith = pCollider;

			if (pCollider->IsTrigger())
			{
				HandleTriggerCollision(pCollider);
				isTrigger = true;
				continue;
			}

			CalculateOverlap(thisPos, thisDim, otherPos, otherDim, dir);

			// One way collision, ignore if the other collider is below this one
			if (pCollider->GetColliderType() == ColliderType::OneWay && dir.y < .0f)
			{
				isOneWay = true;
				continue;
			}

			isColliding = true;
		}

		if (isTrigger || isOneWay) return false;

		if (isColliding)
		{
			const auto pCollisionCallback{ pCollidedWith->GetCollisionCallback() };
			if (pCollisionCallback) pCollisionCallback(GetOwner());
			return true;
		}

		return false;
	}

	void ColliderComponent::AddIgnoreTag(const std::string& tag)
	{
		// Check if the tag is already in the list
		auto it{ std::ranges::find(m_IgnoreTags, tag) };
		if (it != m_IgnoreTags.end()) return;

		m_IgnoreTags.emplace_back(tag);
	}

	void ColliderComponent::RemoveIgnoreTag(const std::string& tag)
	{
		// Check if the tag is in the list
		auto it{ std::ranges::find(m_IgnoreTags, tag) };
		if (it == m_IgnoreTags.end()) return;

		m_IgnoreTags.erase(it);
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
		const float leftX{ (posA.x + dimA.x) - posB.x };
		const float rightX{ posA.x - (posB.x + dimB.x) };
		const float overlapX{ (std::fabsf(leftX) < std::fabsf(rightX)) ? leftX : rightX };

		const float upY{ (posA.y + dimA.y) - posB.y };
		const float downY{ posA.y - (posB.y + dimB.y) };
		const float overlapY{ (std::fabsf(upY) < std::fabsf(downY)) ? upY : downY };

		dir = glm::vec2{ overlapX, overlapY };
	}
}
