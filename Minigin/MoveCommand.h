#pragma once
#include "Command.h"
#include <functional>
#include <glm/glm.hpp>

namespace dae
{
	class TransformComponent;

	class MoveCommand final : public Command
	{
	public:
		// Optional function pointer that gets called when the command is executed using std::function<void()>
		explicit MoveCommand(TransformComponent* transform, const glm::vec2& direction, float moveSpeed, const std::function<void()>& executeFunction = nullptr);
		~MoveCommand() override = default;

		MoveCommand(const MoveCommand& other) = delete;
		MoveCommand(MoveCommand&& other) noexcept = delete;
		MoveCommand& operator=(const MoveCommand& other) = delete;
		MoveCommand& operator=(MoveCommand&& other) noexcept = delete;

		void Execute() override;
		void Undo() override;
	private:
		std::function<void()> m_ExecuteFunction{ nullptr };
		const float m_MoveSpeed{ .0f };
		const glm::vec2 m_Direction{ .0f, .0f };
		glm::vec2 m_LastPosition{ .0f, .0f };

		TransformComponent* m_pTransformComponent{ nullptr };
	};
}
