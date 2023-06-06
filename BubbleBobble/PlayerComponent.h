#pragma once
#include "Component.h"
#include "Observer.h"
#include "Subject.h"

namespace dae
{
	class Command;

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

		void SetSpeed(float speed) { m_Speed = speed; }

	private:
		float m_Speed{ 50.f };

		//void SetupKeyBoardInput();
		//void SetupControllerInput();
	};
}
