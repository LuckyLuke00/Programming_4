#pragma once
#include "Component.h"
#include "Transform.h"

namespace dae
{
	class GameObject;

	class TransformComponent final : public Component
	{
	public:
		explicit TransformComponent(const GameObject* pOwner);
		~TransformComponent() override = default;

		TransformComponent(const TransformComponent& other) = delete;
		TransformComponent(TransformComponent&& other) noexcept = delete;
		TransformComponent& operator=(const TransformComponent& other) = delete;
		TransformComponent& operator=(TransformComponent&& other) noexcept = delete;

		void Update() override;

		const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(float x = .0f, float y = .0f, float z = .0f);

	private:
		glm::vec3 m_Position{ .0f, .0f, .0f };
	};
}

