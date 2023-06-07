#pragma once
#include "Command.h"
#include "Timer.h"
#include <glm/glm.hpp>

namespace dae
{
	class RigidbodyComponent;

	class RigidbodyJumpCommand final : public Command
	{
	public:
		explicit RigidbodyJumpCommand(RigidbodyComponent* rigidBody, const float& jumpForce);
		~RigidbodyJumpCommand() override = default;

		RigidbodyJumpCommand(const RigidbodyJumpCommand& other) = delete;
		RigidbodyJumpCommand(RigidbodyJumpCommand&& other) noexcept = delete;
		RigidbodyJumpCommand& operator=(const RigidbodyJumpCommand& other) = delete;
		RigidbodyJumpCommand& operator=(RigidbodyJumpCommand&& other) noexcept = delete;

		void Execute() override;

	private:
		const float& m_JumpForce; // I don't know a better way te edit the force after the command is created

		RigidbodyComponent* m_pRigidbodyComponent{ nullptr };
	};
}
