#pragma once
#include "Component.h"
#include <glm/glm.hpp>

namespace dae
{
	class TransformComponent;

	class OrbitComponent final : public Component
	{
	public:
		explicit OrbitComponent(GameObject* pOwner);
		~OrbitComponent() override = default;

		OrbitComponent(const OrbitComponent& other) = delete;
		OrbitComponent(OrbitComponent&& other) noexcept = delete;
		OrbitComponent& operator=(const OrbitComponent& other) = delete;
		OrbitComponent& operator=(OrbitComponent&& other) noexcept = delete;

		void Update() override;
		void FixedUpdate() override {};
		void LateUpdate() override {};

		void SetOrbitCenter(const glm::vec3& center) { m_OrbitCenter = center; }
		void SetOrbitSpeed(float speed) { m_OrbitSpeed = speed; }
		void SetOrbitRadius(float radius) { m_OrbitRadius = radius; }

		TransformComponent* m_pTransformComponent{ nullptr };
	private:
		float m_OrbitRadius{ 5.f };
		float m_OrbitSpeed{ 5.f };
		float m_Rotation{ .0f };
		glm::vec3 m_OrbitCenter{ .0f, .0f, .0f };
	};
}
