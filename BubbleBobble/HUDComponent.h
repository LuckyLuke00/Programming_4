#pragma once
#include "Component.h"
#include "Observer.h"
#include "PickupComponent.h"
#include <utility>

namespace dae
{
	class TextComponent;
	class ScoreDisplayComponent;

	class HUDComponent final : public Component, public Observer<PickupType, int>
	{
	public:
		explicit HUDComponent(GameObject* pOwner);
		~HUDComponent() override;

		HUDComponent(const HUDComponent& other) = delete;
		HUDComponent(HUDComponent&& other) noexcept = delete;
		HUDComponent& operator=(const HUDComponent& other) = delete;
		HUDComponent& operator=(HUDComponent&& other) noexcept = delete;

		void CreateHighScoreText();
		void CreateScoreTextBub();
		void CreateScoreTextBob();

	private:
		void UpdateText();

		void OnNotify(PickupType type, int playerId) override;

		float m_Margin{ 5.f };
		ScoreDisplayComponent* m_pHighScoreText{};
		ScoreDisplayComponent* m_pScoreTextBub{};
		ScoreDisplayComponent* m_pScoreTextBob{};
	};
}
