#pragma once
#include "Component.h"
#include "TextComponent.h"
#include "TransformComponent.h"
#include <utility>

namespace dae
{
	class TransformComponent;
	class TextComponent;

	class ScoreDisplayComponent final : public Component
	{
	public:
		explicit ScoreDisplayComponent(GameObject* pOwner);
		~ScoreDisplayComponent() override = default;

		ScoreDisplayComponent(const ScoreDisplayComponent& other) = delete;
		ScoreDisplayComponent(ScoreDisplayComponent&& other) noexcept = delete;
		ScoreDisplayComponent& operator=(const ScoreDisplayComponent& other) = delete;
		ScoreDisplayComponent& operator=(ScoreDisplayComponent&& other) noexcept = delete;

		void SetTitleText(const std::string& title) { m_pScoreText.first->SetText(title); }
		void SetTitleColor(const SDL_Color& color) { m_pScoreText.first->SetColor(color); }
		void SetPosition(const glm::vec2& pos);

		void SetScoreText(int score) { m_pScoreText.second->SetText(std::to_string(score)); }
		void CenterHorizontally();
		void AlignRight();
		void AlignLeft();
		void Offset(const glm::vec2& offset);

	private:
		int m_FontSize{ 10 };

		std::pair<TextComponent*, TextComponent*> m_pScoreText{};
		std::pair<TransformComponent*, TransformComponent*> m_pTransforms{};

		void CreateTitleText();
		void CreateScoreText();
	};
}
