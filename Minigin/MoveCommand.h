#pragma once
#include "Command.h"
#include <glm/glm.hpp>

namespace dae
{
	class TransformComponent;

	class MoveCommand final : public Command
	{
	public:
		explicit MoveCommand(GameObject* gameObject, const glm::vec3& direction, float moveSpeed);
		~MoveCommand() override = default;

		MoveCommand(const MoveCommand& other) = delete;
		MoveCommand(MoveCommand&& other) noexcept = delete;
		MoveCommand& operator=(const MoveCommand& other) = delete;
		MoveCommand& operator=(MoveCommand&& other) noexcept = delete;

		void Execute() override;
		void Undo() override;
	private:
		const float m_MoveSpeed{ .0f };
		const glm::vec3 m_Direction{ .0f, .0f, .0f };

		TransformComponent* m_pTransformComponent{ nullptr };
	};
}
