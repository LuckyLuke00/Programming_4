#pragma once
#include "Singleton.h"
#include "ColliderComponent.h"
#include <vector>
#include <span>
#include <algorithm>

namespace dae
{
	class CollisionSystem final : public Singleton<CollisionSystem>
	{
	public:
		void AddCollider(ColliderComponent* pCollider)
		{
			// Check if the collider is already in the list
			auto it{ std::ranges::find(m_pColliders, pCollider) };
			if (it == m_pColliders.end()) m_pColliders.emplace_back(pCollider);
		}

		void RemoveCollider(ColliderComponent* pCollider)
		{
			auto it{ std::ranges::find(m_pColliders, pCollider) };
			if (it != m_pColliders.end()) m_pColliders.erase(it);
		}

		std::span<ColliderComponent* const> GetColliders() const { return m_pColliders; }

	private:
		std::vector<ColliderComponent*> m_pColliders;

		friend class Singleton<CollisionSystem>;
		explicit CollisionSystem() = default;
	};
}
