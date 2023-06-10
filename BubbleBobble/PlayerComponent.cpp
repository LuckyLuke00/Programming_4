#include "PlayerComponent.h"
#include "GameObject.h"
#include "RenderTextureComponent.h"
#include "ColliderComponent.h"
#include "InputManager.h"
#include "Renderer.h"
#include "GameManager.h"
#include <iostream>

namespace dae
{
	int PlayerComponent::m_PlayerCount{ -1 };

	PlayerComponent::PlayerComponent(GameObject* pOwner) :
		Component{ pOwner },
		m_pTransformComponent{ pOwner->AddComponent<dae::TransformComponent>() },
		m_pRenderSpriteComponent{ pOwner->AddComponent<dae::RenderSpriteComponent>() },
		m_pColliderComponent{ pOwner->AddComponent<dae::ColliderComponent>() },
		m_pRigidBodyComponent{ pOwner->AddComponent<dae::RigidbodyComponent>() }

	{
		++m_PlayerCount;
		m_PlayerId = m_PlayerCount;

		m_pRigidBodyComponent->SetMaxVelocity({ m_Speed, m_JumpForce });

		// Only the first player will use keyboard input
		SetupKeyBoardInput();
		SetupControllerInput();

		pOwner->SetRenderOrder(1);

		Respawn();
	}

	void PlayerComponent::Update()
	{
		HandleState();
		WrapAroundScreen();
	}

	void PlayerComponent::SetSpeed(float speed)
	{
		m_Speed = speed; // Automatically updates the speed in the command, since the command uses a reference to the speed
		m_pRigidBodyComponent->SetMaxVelocity({ m_Speed, m_JumpForce });
	}

	void PlayerComponent::SetJumpForce(float jumpForce)
	{
		m_JumpForce = jumpForce; // Automatically updates the jump force in the command, since the command uses a reference to the jump force
		m_pRigidBodyComponent->SetMaxVelocity({ m_Speed, m_JumpForce });
	}

	void PlayerComponent::AddAnimation(const std::string& name, const SpriteAnimation& animation)
	{
		// No need to perform null checks, since the constructor already adds the components
		m_pRenderSpriteComponent->AddAnimation(name, animation);
		m_pColliderComponent->SetDimensions(m_pRenderSpriteComponent->GetFrameSize());
	}

	void PlayerComponent::SetState(PlayerState state)
	{
		if (m_State == state) return;

		switch (state)
		{
		case PlayerState::Idle:
			m_pRenderSpriteComponent->SetAnimation("Idle");
			break;
		case PlayerState::Walk:
			m_pRenderSpriteComponent->SetAnimation("Walk");
			break;
		case PlayerState::Jump:
			m_pRenderSpriteComponent->SetAnimation("Jump");
			break;
		case PlayerState::Fall:
			m_pRenderSpriteComponent->SetAnimation("Fall");
			break;
		case PlayerState::Shoot:
			m_pRenderSpriteComponent->SetAnimation("Shoot");
			break;
		case PlayerState::Death:
			m_pRenderSpriteComponent->SetAnimation("Death");
			break;
		default:
			break;
		}

		m_State = state;
	}

	void PlayerComponent::SetupKeyBoardInput()
	{
		// Left
		auto& keyboard{ InputManager::GetInstance().GetKeyboard() };

		auto moveCommand{ std::make_unique<RigidbodyMoveCommand>(m_pRigidBodyComponent, glm::vec2{ -1.f, .0f }, m_Speed) };
		keyboard.AddCommand(std::move(moveCommand), InputState::Down, SDL_SCANCODE_A);

		// Right
		moveCommand = std::make_unique<RigidbodyMoveCommand>(m_pRigidBodyComponent, glm::vec2{ 1.f, .0f }, m_Speed);
		InputManager::GetInstance().GetKeyboard().AddCommand(std::move(moveCommand), InputState::Down, SDL_SCANCODE_D);

		// Jump
		auto jumpCommand{ std::make_unique<RigidbodyJumpCommand>(m_pRigidBodyComponent, m_JumpForce) };
		InputManager::GetInstance().GetKeyboard().AddCommand(std::move(jumpCommand), InputState::Down, SDL_SCANCODE_SPACE);
	}

	void PlayerComponent::SetupControllerInput()
	{
		auto controller{ InputManager::GetInstance().AddXboxController() };

		// Left
		auto moveCommand{ std::make_unique<RigidbodyMoveCommand>(m_pRigidBodyComponent, glm::vec2{ -1.f, .0f }, m_Speed) };
		controller->AddCommand(std::move(moveCommand), InputState::Down, XboxController::XboxButton::DPadLeft);

		// Right
		moveCommand = std::make_unique<RigidbodyMoveCommand>(m_pRigidBodyComponent, glm::vec2{ 1.f, .0f }, m_Speed);
		controller->AddCommand(std::move(moveCommand), InputState::Down, XboxController::XboxButton::DPadRight);

		// Jump
		auto jumpCommand{ std::make_unique<RigidbodyJumpCommand>(m_pRigidBodyComponent, m_JumpForce) };
		controller->AddCommand(std::move(jumpCommand), InputState::Down, XboxController::XboxButton::A);
	}

	void PlayerComponent::Respawn()
	{
		const auto& level{ GameManager::GetInstance().GetCurrentLevel() };
		if (!level) return;

		const float levelScale{ level->GetLevelScale() };

		// Subtract a quarter of the scale, so the player is centered
		const float scale{ levelScale - (levelScale / 4.f) };
		m_pTransformComponent->SetScale(scale); // Set the scale of the player based on the level scale

		glm::vec2 spawnPos{ level->GetPlayerSpawnPosition(m_PlayerId) };
		m_pTransformComponent->SetPosition(spawnPos);

		// If the players position is over the half of the screen, flip the sprite
		int width;
		int height;
		Renderer::GetInstance().GetWindowSize(width, height);

		if (spawnPos.x < static_cast<float>(width) * .5f)
		{
			m_pRenderSpriteComponent->SetFlipX(true);
		}
	}

	void PlayerComponent::HandleState()
	{
		const auto& velocity{ m_pRigidBodyComponent->GetVelocity() };

		const bool IsMoving{ m_pRigidBodyComponent->IsMoving() };
		const bool IsGrounded{ m_pRigidBodyComponent->IsGrounded() };

		if (IsMoving && IsGrounded)
		{
			SetState(PlayerState::Walk);
		}
		else if (!IsGrounded && velocity.y > FLT_EPSILON)
		{
			SetState(PlayerState::Fall);
		}
		else if (!IsGrounded && velocity.y < FLT_EPSILON)
		{
			SetState(PlayerState::Jump);
		}
		else
		{
			SetState(PlayerState::Idle);
		}

		// Set the flip but prevent from flipping back when not moving, by getting the flip from the sprite component
		if (velocity.x > FLT_EPSILON)
		{
			m_pRenderSpriteComponent->SetFlipX(true);
		}
		else if (velocity.x < -FLT_EPSILON)
		{
			m_pRenderSpriteComponent->SetFlipX(false);
		}
	}

	void PlayerComponent::WrapAroundScreen()
	{
		int width;
		int height;
		Renderer::GetInstance().GetWindowSize(width, height);

		// Check if the player is out of the screen
		const auto& pos{ m_pTransformComponent->GetWorldPosition() };
		const glm::vec2& frameSize{ m_pRenderSpriteComponent->GetFrameSize() };

		if (pos.y > static_cast<float>(height))
		{
			m_pTransformComponent->SetPosition(pos.x, .0f - frameSize.y);
		}

		if (pos.x > static_cast<float>(width))
		{
			m_pTransformComponent->SetPosition(.0f - frameSize.x, pos.y);
		}
		else if (pos.x < .0f - frameSize.x)
		{
			m_pTransformComponent->SetPosition(static_cast<float>(width), pos.y);
		}
	}
}
