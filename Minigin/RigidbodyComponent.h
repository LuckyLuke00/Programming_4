#pragma once
#include "Component.h"
#include "Observer.h"
#include "Subject.h"
#include <glm/glm.hpp>
#include <iostream>
namespace dae
{
	class TransformComponent;
	class ColliderComponent;
	class CollisionEvent;

	class RigidbodyComponent final : public Component
	{
	public:
		explicit RigidbodyComponent(GameObject* pOwner);
		~RigidbodyComponent() override = default;

		RigidbodyComponent(const RigidbodyComponent& other) = delete;
		RigidbodyComponent(RigidbodyComponent&& other) noexcept = delete;
		RigidbodyComponent& operator=(const RigidbodyComponent& other) = delete;
		RigidbodyComponent& operator=(RigidbodyComponent&& other) noexcept = delete;

		void Update() override;

		bool IsGrounded() const { return m_IsGrounded; }
		bool IsMoving() const { return std::fabs(m_Velocity.x) > FLT_EPSILON || std::fabs(m_Velocity.y) > FLT_EPSILON; }

		const glm::vec2& GetVelocity() const { return m_Velocity; }
		TransformComponent* GetTransform() const { return m_pTransformComponent; }

		void SetGravity(float gravity) { m_Gravity = gravity; }
		void EnableGravity(bool enabled) { m_GravityEnabled = enabled; }
		void SetVelocity(const glm::vec2& velocity) { m_Velocity = velocity; }
		void SetMaxVelocity(const glm::vec2& maxVelocity) { m_MaxVelocity = maxVelocity; }

		void AddForce(const glm::vec2& force);

	private:
		ColliderComponent* m_pColliderComponent{ nullptr };
		TransformComponent* m_pTransformComponent{ nullptr };

		bool m_GravityEnabled{ true };
		bool m_IsGrounded{ false };
		float m_Friction{ 500.f };
		float m_Gravity{ 9.81f * 10.f };
		glm::vec2 m_MaxVelocity{ 50.f, 50.f };
		glm::vec2 m_Velocity{ .0f, .0f };
	};
}
