#pragma once
#include "Singleton.h"
#include "ColliderComponent.h"
#include <vector>
#include <span>

namespace dae
{
	class CollisionSystem final : public Singleton<CollisionSystem>
	{
	public:
		void AddCollider(ColliderComponent* pCollider) { m_pColliders.emplace_back(pCollider); }
		void RemoveCollider(ColliderComponent* pCollider) { m_pColliders.erase(std::remove(m_pColliders.begin(), m_pColliders.end(), pCollider), m_pColliders.end()); }

		std::span<ColliderComponent* const> GetColliders() const { return m_pColliders; }
	private:
		std::vector<ColliderComponent*> m_pColliders;

		friend class Singleton<CollisionSystem>;
		explicit CollisionSystem() = default;
	};
}
