#pragma once
#include "CollisionEvent.h"
#include "Component.h"
#include <memory>
#include <glm/glm.hpp>

namespace dae
{
	class RigidBodyComponent;

	// Enum class that specifies if it's a one way collider or not
	enum class ColliderType
	{
		Normal,
		OneWay
	};

	class ColliderComponent final : public Component
	{
	public:
		explicit ColliderComponent(GameObject* pOwner);
		~ColliderComponent() override;

		ColliderComponent(const ColliderComponent& other) = delete;
		ColliderComponent(ColliderComponent&& other) noexcept = delete;
		ColliderComponent& operator=(const ColliderComponent& other) = delete;
		ColliderComponent& operator=(ColliderComponent&& other) noexcept = delete;

		bool IsColliding(glm::vec2& dir) const;

		// Getter for the position
		CollisionEvent* GetCollisionEvent() const { return m_pCollisionEvent.get(); }
		const ColliderType& GetColliderType() const { return m_ColliderType; }
		const glm::vec2& GetDimensions() const { return m_Dimensions; }

		void SetColliderType(const ColliderType& colliderType) { m_ColliderType = colliderType; }
		void SetDimensions(const glm::vec2& dimensions) { m_Dimensions = dimensions; }

	private:
		ColliderType m_ColliderType{ ColliderType::Normal };
		glm::vec2 m_CollisionDirection{ .0f, .0f };
		glm::vec2 m_Dimensions{ .0f, .0f };

		std::unique_ptr<CollisionEvent> m_pCollisionEvent{ nullptr };
	};
}
