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
		explicit RigidbodyJumpCommand(RigidbodyComponent* rigidBody, float jumpForce);
		~RigidbodyJumpCommand() override = default;

		RigidbodyJumpCommand(const RigidbodyJumpCommand& other) = delete;
		RigidbodyJumpCommand(RigidbodyJumpCommand&& other) noexcept = delete;
		RigidbodyJumpCommand& operator=(const RigidbodyJumpCommand& other) = delete;
		RigidbodyJumpCommand& operator=(RigidbodyJumpCommand&& other) noexcept = delete;

		void Execute() override;

		void SetJumpForce(float jumpForce) { m_JumpForce = jumpForce; }

	private:
		float m_JumpForce{ 50.f };

		RigidbodyComponent* m_pRigidbodyComponent{ nullptr };
	};
}
