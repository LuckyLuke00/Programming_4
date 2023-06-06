#pragma once
#include "CollisionEvent.h"
#include "Component.h"
#include <memory>
#include <glm/glm.hpp>

namespace dae
{
	class RigidBodyComponent;

	class ColliderComponent : public Component
	{
	public:
		explicit ColliderComponent(GameObject* pOwner);
		~ColliderComponent() override;

		ColliderComponent(const ColliderComponent& other) = delete;
		ColliderComponent(ColliderComponent&& other) noexcept = delete;
		ColliderComponent& operator=(const ColliderComponent& other) = delete;
		ColliderComponent& operator=(ColliderComponent&& other) noexcept = delete;

		void Update() override;

		bool IsColliding(const ColliderComponent* other, glm::vec2& dir) const;

		CollisionEvent* GetCollisionEvent() const { return m_pCollisionEvent.get(); }

		const glm::vec2& GetDimensions() const { return m_Dimensions; }
		void SetDimensions(const glm::vec2& dimensions) { m_Dimensions = dimensions; }

	private:
		glm::vec2 m_CollisionDirection{ .0f, .0f };
		glm::vec2 m_Dimensions{ .0f, .0f };

		RigidBodyComponent* m_pRigidBodyComponent{ nullptr };
		std::unique_ptr<CollisionEvent> m_pCollisionEvent{ nullptr };
	};
}
