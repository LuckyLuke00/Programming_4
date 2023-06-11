#pragma once
#include "Component.h"
#include <functional>
#include <string>
#include <glm/vec2.hpp>

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
		bool IsTrigger() const { return m_IsTrigger; }

		void SetIsTrigger(bool isTrigger) { m_IsTrigger = isTrigger; }
		void SetTriggerCallback(const std::function<void(const GameObject*)>& callback) { m_pTriggerCallback = callback; }
		std::function<void(const GameObject*)> GetTriggerCallback() const { return m_pTriggerCallback; }

		const ColliderType& GetColliderType() const { return m_ColliderType; }
		const glm::vec2& GetDimensions() const { return m_Dimensions; }

		void SetColliderType(const ColliderType& colliderType) { m_ColliderType = colliderType; }
		void SetDimensions(const glm::vec2& dimensions) { m_Dimensions = dimensions; }

		void AddIgnoreTag(const std::string& tag);
		const std::vector<std::string>& GetIgnoreTags() const { return m_IgnoreTags; }

	private:
		bool m_IsTrigger{ false };

		ColliderType m_ColliderType{ ColliderType::Normal };

		glm::vec2 m_CollisionDirection{ .0f, .0f };
		glm::vec2 m_Dimensions{ .0f, .0f };

		std::function<void(const GameObject*)> m_pTriggerCallback{ nullptr };
		std::vector<std::string> m_IgnoreTags{};

		bool CheckCollision(const glm::vec2& posA, const glm::vec2& dimA, const glm::vec2& posB, const glm::vec2& dimB) const;
		void HandleTriggerCollision(const ColliderComponent* pOther) const;
		void CalculateOverlap(const glm::vec2& posA, const glm::vec2& dimA, const glm::vec2& posB, const glm::vec2& dimB, glm::vec2& dir) const;
	};
}
