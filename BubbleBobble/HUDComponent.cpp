#include "HUDComponent.h"
#include "GameObject.h"
#include "RenderTextureComponent.h"
#include "TextComponent.h"
#include "ScoreDisplayComponent.h"
#include "Renderer.h"

namespace dae
{
	HUDComponent::HUDComponent(GameObject* pOwner) :
		Component{ pOwner }
	{
		CreateHighScoreText();
		CreateScoreTextBub();
		CreateScoreTextBob();
	}

	void HUDComponent::CreateHighScoreText()
	{
		auto go{ std::make_shared<GameObject>() };
		m_pHighScoreText = go->AddComponent<ScoreDisplayComponent>();

		m_pHighScoreText->SetTitleText("HIGHSCORE");
		m_pHighScoreText->SetTitleColor(SDL_Color{ 255, 0, 0, 255 });

		m_pHighScoreText->SetScoreText(0);

		// Position in the middle of the screen
		m_pHighScoreText->SetPosition(glm::vec2{ .0f, m_Margin });
		m_pHighScoreText->CenterHorizontally();
	}

	void HUDComponent::CreateScoreTextBub()
	{
		auto go{ std::make_shared<GameObject>() };
		m_pScoreTextBub = go->AddComponent<ScoreDisplayComponent>();

		m_pScoreTextBub->SetTitleText("INSERT COIN");
		m_pScoreTextBub->SetTitleColor(SDL_Color{ 0, 255, 0, 255 });

		m_pScoreTextBub->SetScoreText(0);

		m_pScoreTextBub->SetPosition(glm::vec2{ .0f, m_Margin });
		m_pScoreTextBub->AlignLeft();
		m_pScoreTextBub->Offset(glm::vec2{ m_Margin, .0f });
	}

	void HUDComponent::CreateScoreTextBob()
	{
		auto go{ std::make_shared<GameObject>() };
		m_pScoreTextBob = go->AddComponent<ScoreDisplayComponent>();

		m_pScoreTextBob->SetTitleText("INSERT COIN");
		m_pScoreTextBob->SetTitleColor(SDL_Color{ 0, 0, 255, 255 });

		m_pScoreTextBob->SetScoreText(0);

		m_pScoreTextBob->SetPosition(glm::vec2{ .0f, m_Margin });
		m_pScoreTextBob->AlignRight();
		m_pScoreTextBob->Offset(glm::vec2{ -m_Margin, .0f });
	}
}
