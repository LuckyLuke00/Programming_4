#pragma once
#include "Component.h"
#include <glm/glm.hpp>

namespace dae
{
	class GameObject;

	class TransformComponent final : public Component
	{
	public:
		explicit TransformComponent(GameObject* pOwner);
		~TransformComponent() override = default;

		TransformComponent(const TransformComponent& other) = delete;
		TransformComponent(TransformComponent&& other) noexcept = delete;
		TransformComponent& operator=(const TransformComponent& other) = delete;
		TransformComponent& operator=(TransformComponent&& other) noexcept = delete;

		void Update() override {};
		void FixedUpdate() override {};
		void LateUpdate() override {};

		const glm::vec3& GetLocalPosition() const { return m_LocalPosition; }
		const glm::vec3& GetWorldPosition();
		void SetPosition(const glm::vec3& position) { SetPosition(position.x, position.y, position.z); }
		void SetPosition(float x = .0f, float y = .0f, float z = .0f);

		void SetDirty();
	private:
		bool m_IsDirty{ true };
		glm::vec3 m_LocalPosition{ .0f, .0f, .0f };
		glm::vec3 m_WorldPosition{ .0f, .0f, .0f };

		void UpdateTransform();
	};
}
