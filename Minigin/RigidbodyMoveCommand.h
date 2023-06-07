#pragma once
#include "Command.h"
#include "Timer.h"
#include <glm/glm.hpp>

namespace dae
{
	class RigidbodyComponent;

	class RigidbodyMoveCommand final : public Command
	{
	public:
		explicit RigidbodyMoveCommand(RigidbodyComponent* rigidBody, const glm::vec2& direction, const float& speed);
		~RigidbodyMoveCommand() override = default;

		RigidbodyMoveCommand(const RigidbodyMoveCommand& other) = delete;
		RigidbodyMoveCommand(RigidbodyMoveCommand&& other) noexcept = delete;
		RigidbodyMoveCommand& operator=(const RigidbodyMoveCommand& other) = delete;
		RigidbodyMoveCommand& operator=(RigidbodyMoveCommand&& other) noexcept = delete;

		void Execute() override;

	private:
		const glm::vec2 m_Direction{ .0f, .0f };
		const float& m_Speed; // I don't know a better way te edit the speed after the command is created

		RigidbodyComponent* m_pRigidbodyComponent{ nullptr };
	};
}
