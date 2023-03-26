#pragma once
#include "Command.h"
#include <glm/glm.hpp>

namespace dae
{
	class TransformComponent;

	class Move2DCommand final : public Command
	{
	public:
		explicit Move2DCommand(GameObject* gameObject, const glm::vec3& direction, float moveSpeed);
		~Move2DCommand() override = default;

		Move2DCommand(const Move2DCommand& other) = delete;
		Move2DCommand(Move2DCommand&& other) noexcept = delete;
		Move2DCommand& operator=(const Move2DCommand& other) = delete;
		Move2DCommand& operator=(Move2DCommand&& other) noexcept = delete;

		void Execute() override;
		void Undo() override;
	private:
		const float m_MoveSpeed{ .0f };
		const glm::vec3 m_Direction{ .0f, .0f, .0f };
		glm::vec3 m_LastPosition{ .0f, .0f, .0f };

		TransformComponent* m_pTransformComponent{ nullptr };
	};
}
