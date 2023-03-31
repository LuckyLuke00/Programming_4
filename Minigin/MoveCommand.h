#pragma once
#include "Command.h"
#include <glm/glm.hpp>

namespace dae
{
	class TransformComponent;

	class MoveCommand final : public Command
	{
	public:
		explicit MoveCommand(TransformComponent* transform, const glm::vec2& direction, float moveSpeed);
		~MoveCommand() override = default;

		MoveCommand(const MoveCommand& other) = delete;
		MoveCommand(MoveCommand&& other) noexcept = delete;
		MoveCommand& operator=(const MoveCommand& other) = delete;
		MoveCommand& operator=(MoveCommand&& other) noexcept = delete;

		void Execute() override;
		void Undo() override;
	private:
		const float m_MoveSpeed{ .0f };
		const glm::vec2 m_Direction{ .0f, .0f };
		glm::vec2 m_LastPosition{ .0f, .0f };

		TransformComponent* m_pTransformComponent{ nullptr };
	};
}
