#pragma once
#include "Component.h"

namespace dae
{
	class GameStateComponent final : public Component
	{
	public:
		explicit GameStateComponent(GameObject* pOwner);
		~GameStateComponent() override = default;

		GameStateComponent(const GameStateComponent& other) = delete;
		GameStateComponent(GameStateComponent&& other) noexcept = delete;
		GameStateComponent& operator=(const GameStateComponent& other) = delete;
		GameStateComponent& operator=(GameStateComponent&& other) noexcept = delete;

		void Update() override;

	private:
		float m_LevelCompleteTimer{ .0f };
		float m_LevelCompleteTime{ 10.f };
	};
}
