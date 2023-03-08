#pragma once
#include "Component.h"
#include <glm/glm.hpp>

namespace dae
{
	class TransformComponent;

	class RotatorComponent final : public Component
	{
	public:
		explicit RotatorComponent(GameObject* pOwner);
		~RotatorComponent() override = default;

		RotatorComponent(const RotatorComponent& other) = delete;
		RotatorComponent(RotatorComponent&& other) noexcept = delete;
		RotatorComponent& operator=(const RotatorComponent& other) = delete;
		RotatorComponent& operator=(RotatorComponent&& other) noexcept = delete;

		void Update() override;
		void FixedUpdate() override {};
		void LateUpdate() override {};

		void SetRotationCenter(const glm::vec3& center) { m_OrbitCenter = center; }
		void SetRotationSpeed(float speed) { m_OrbitSpeed = speed; }
		void SetRotationRadius(float radius) { m_OrbitRadius = radius; }

	private:
		TransformComponent* m_pTransformComponent{ nullptr };
		float m_OrbitRadius{ 5.f };
		float m_OrbitSpeed{ 5.f };
		float m_Rotation{ .0f };
		glm::vec3 m_OrbitCenter{ .0f, .0f, .0f };
	};
}
