#pragma once
#include "Subject.h"
#include <glm/glm.hpp>

namespace dae
{
	class ColliderComponent;

	class CollisionEvent final : public Subject<CollisionEvent>
	{
	public:
		explicit CollisionEvent() = default;
		~CollisionEvent() override = default;

		void Notify(ColliderComponent* pOtherCollider, ColliderComponent* pThisCollider, const glm::vec2& dir);

		ColliderComponent* GetOtherCollider() const { return m_pOtherCollider; }
		ColliderComponent* GetThisCollider() const { return m_pThisCollider; }

		const glm::vec2& GetCollisionDirection() const { return m_CollisionDirection; }

	private:
		ColliderComponent* m_pOtherCollider{ nullptr };
		ColliderComponent* m_pThisCollider{ nullptr };

		glm::vec2 m_CollisionDirection{ .0f, .0f };
	};
}
