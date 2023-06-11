#pragma once
#include "TransformComponent.h"
#include <string>
#include <vector>
#include <memory>

namespace dae
{
	class ColliderComponent;
	class RenderSpriteComponent;
	class RigidbodyComponent;
	class TransformComponent;
	struct SpriteAnimation;

	enum class PlayerState
	{
		Death,
		Fall,
		Idle,
		Jump,
		Shoot,
		Walk
	};

	class PlayerComponent final : public Component
	{
	public:
		explicit PlayerComponent(GameObject* pOwner);
		~PlayerComponent() override = default;

		PlayerComponent(const PlayerComponent& other) = delete;
		PlayerComponent(PlayerComponent&& other) noexcept = delete;
		PlayerComponent& operator=(const PlayerComponent& other) = delete;
		PlayerComponent& operator=(PlayerComponent&& other) noexcept = delete;

		void Update() override;

		void SetSpeed(float speed);
		void SetJumpForce(float jumpForce);

		void AddAnimation(const std::string& name, const SpriteAnimation& animation);

		void SetPosition(const glm::vec2& pos) { m_pTransformComponent->SetPosition(pos); }
		glm::vec2 GetPosition() const { return m_pTransformComponent->GetWorldPosition(); }

		int GetPlayerId() const { return m_PlayerId; }

		// Getters and setters for the state
		PlayerState GetState() const { return m_State; }
		void SetState(PlayerState state);

		void Respawn();
		bool IsDead() const { return m_State == PlayerState::Death; }
	private:
		static int m_PlayerCount;
		int m_PlayerId{ -1 };
		float m_Speed{ 50.f };
		float m_JumpForce{ 130.f };

		float m_DeathTimer{ 0.f };
		float m_DeathTime{ 2.f };

		std::string m_TexturePath{ "" };

		PlayerState m_State{ -1 };

		TransformComponent* m_pTransformComponent{ nullptr };
		RenderSpriteComponent* m_pRenderSpriteComponent{ nullptr };
		ColliderComponent* m_pColliderComponent{ nullptr };
		RigidbodyComponent* m_pRigidbodyComponent{ nullptr };

		void SetupKeyBoardInput();
		void SetupControllerInput();

		void HandleState();
		void WrapAroundScreen();
		void HandleSpriteFlip();

		void BlowBubble();
		void OnCollision(const GameObject* other);
	};
}
