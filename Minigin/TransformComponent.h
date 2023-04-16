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

		const glm::vec2& GetLocalPosition() const { return m_LocalPosition; }
		const glm::vec2& GetWorldPosition();
		void SetPosition(const glm::vec2& position) { SetPosition(position.x, position.y); }
		void SetPosition(float x = .0f, float y = .0f);
		void Translate(const glm::vec2& translation) { Translate(translation.x, translation.y); }
		void Translate(float x = .0f, float y = .0f);

		void SetDirty();
	private:
		bool m_IsDirty{ true };
		glm::vec2 m_LocalPosition{ .0f, .0f };
		glm::vec2 m_WorldPosition{ .0f, .0f };

		void UpdateTransform();
	};
}
