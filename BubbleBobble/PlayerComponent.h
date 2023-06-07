#pragma once
#include "TransformComponent.h"
#include "RigidbodyComponent.h"
#include "RigidbodyMoveCommand.h"
#include "RigidbodyJumpCommand.h"
#include <memory>
#include <string>

namespace dae
{
	class ColliderComponent;
	class RenderTextureComponent;
	class RigidbodyComponent;
	class TransformComponent;

	class PlayerComponent final : public Component
	{
	public:
		explicit PlayerComponent(GameObject* pOwner);
		~PlayerComponent() override;

		PlayerComponent(const PlayerComponent& other) = delete;
		PlayerComponent(PlayerComponent&& other) noexcept = delete;
		PlayerComponent& operator=(const PlayerComponent& other) = delete;
		PlayerComponent& operator=(PlayerComponent&& other) noexcept = delete;

		void Update() override;

		void SetSpeed(float speed);
		void SetJumpForce(float jumpForce);

		void SetTexturePath(const std::string& path);
		void SetPosition(const glm::vec2& pos) { m_pTransformComponent->SetPosition(pos); }

	private:
		float m_Speed{ 50.f };
		float m_JumpForce{ 130.f };
		std::string m_TexturePath{ "" };

		TransformComponent* m_pTransformComponent{ nullptr };
		RenderTextureComponent* m_pRenderTextureComponent{ nullptr };
		ColliderComponent* m_pColliderComponent{ nullptr };
		RigidbodyComponent* m_pRigidBodyComponent{ nullptr };

		void SetupKeyBoardInput();
		void SetupControllerInput();
	};
}