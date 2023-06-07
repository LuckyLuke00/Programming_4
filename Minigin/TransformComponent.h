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

		float GetScale();
		const glm::vec2& GetLocalPosition();
		const glm::vec2& GetWorldPosition();
		void SetPosition(const glm::vec2& position) { SetPosition(position.x, position.y); }
		void SetPosition(float x = .0f, float y = .0f);
		void SetScale(float scale) { m_Scale = scale; SetDirty(); }
		void Translate(const glm::vec2& translation) { Translate(translation.x, translation.y); }
		void Translate(float x = .0f, float y = .0f);

		void SetDirty();
	private:
		bool m_IsDirty{ true };
		glm::vec2 m_LocalPosition{ .0f, .0f };
		glm::vec2 m_WorldPosition{ .0f, .0f };
		float m_Scale{ 1.f };

		void UpdateTransform();
	};
}
