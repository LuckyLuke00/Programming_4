#pragma once
#include "Component.h"
#include "Transform.h"

namespace dae
{
	class GameObject;

	class TransformComponent final : public Component
	{
	public:
		explicit TransformComponent(const GameObject* pOwner, float x = .0f, float y = .0f, float z = .0f);
		~TransformComponent() override = default;

		TransformComponent(const TransformComponent& other) = delete;
		TransformComponent(TransformComponent&& other) noexcept = delete;
		TransformComponent& operator=(const TransformComponent& other) = delete;
		TransformComponent& operator=(TransformComponent&& other) noexcept = delete;

		void Update() override;

		const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(float x, float y, float z);

	private:
		Transform m_Transform{};
		glm::vec3 m_Position;
	};
}

