#include "PlayerComponent.h"
#include "GameObject.h"
#include "RenderTextureComponent.h"
#include "ColliderComponent.h"
#include "InputManager.h"
#include "GameManager.h"
#include <iostream>

namespace dae
{
	PlayerComponent::PlayerComponent(GameObject* pOwner) :
		Component{ pOwner },
		m_pTransformComponent{ pOwner->AddComponent<dae::TransformComponent>() },
		m_pRenderSpriteComponent{ pOwner->AddComponent<dae::RenderSpriteComponent>() },
		m_pColliderComponent{ pOwner->AddComponent<dae::ColliderComponent>() },
		m_pRigidBodyComponent{ pOwner->AddComponent<dae::RigidbodyComponent>() }

	{
		m_pRigidBodyComponent->SetMaxVelocity({ m_Speed, m_JumpForce });

		// Only the first player will use keyboard input
		SetupKeyBoardInput();
		SetupControllerInput();

		const float levelScale{ GameManager::GetInstance().GetCurrentLevel().GetLevelScale() };

		// Subtract a quarter of the scale, so the player is centered
		const float scale{ levelScale - (levelScale / 4.f) };
		m_pTransformComponent->SetScale(scale);

		pOwner->SetRenderOrder(1);
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
		if (!m_pRenderSpriteComponent) return;
		m_pRenderSpriteComponent->AddAnimation(name, animation);

		if (!m_pColliderComponent) return;
		m_pColliderComponent->SetDimensions(m_pRenderSpriteComponent->GetFrameSize());
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
}
