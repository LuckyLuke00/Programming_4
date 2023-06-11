#include "ScoreDisplayComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "SceneManager.h"
#include "RenderTextureComponent.h"
#include "Scene.h"
#include "Renderer.h"

namespace dae
{
	ScoreDisplayComponent::ScoreDisplayComponent(GameObject* pOwner) :
		Component{ pOwner }
	{
		CreateTitleText();
		CreateScoreText();
	}

	void ScoreDisplayComponent::SetPosition(const glm::vec2& pos)
	{
		m_pTransforms.first->SetPosition(pos);

		const glm::vec2 titleSize{ m_pScoreText.first->GetTextSize() };
		const glm::vec2 scoreSize{ m_pScoreText.second->GetTextSize() };

		// Center underneath title
		m_pTransforms.second->SetPosition(pos.x + (titleSize.x - scoreSize.x) * .5f, pos.y + titleSize.y);
	}

	void ScoreDisplayComponent::CenterHorizontally()
	{
		int width;
		int height;
		Renderer::GetInstance().GetWindowSize(width, height);

		const glm::vec2 titleSize{ m_pScoreText.first->GetTextSize() };

		SetPosition(glm::vec2{ (static_cast<float>(width) - titleSize.x) * .5f, m_pTransforms.first->GetWorldPosition().y });
	}

	void ScoreDisplayComponent::AlignRight()
	{
		int width;
		int height;
		Renderer::GetInstance().GetWindowSize(width, height);

		const glm::vec2 titleSize{ m_pScoreText.first->GetTextSize() };

		SetPosition(glm::vec2{ static_cast<float>(width) - titleSize.x, m_pTransforms.first->GetWorldPosition().y });
	}

	void ScoreDisplayComponent::AlignLeft()
	{
		int width;
		int height;
		Renderer::GetInstance().GetWindowSize(width, height);

		SetPosition(glm::vec2{ 0.f, m_pTransforms.first->GetWorldPosition().y });
	}

	void ScoreDisplayComponent::Offset(const glm::vec2& offset)
	{
		m_pTransforms.first->SetPosition(m_pTransforms.first->GetWorldPosition() + offset);
		m_pTransforms.second->SetPosition(m_pTransforms.second->GetWorldPosition() + offset);
	}

	void ScoreDisplayComponent::CreateTitleText()
	{
		auto title{ std::make_shared<GameObject>() };
		m_pTransforms.first = title->AddComponent<TransformComponent>();

		title->AddComponent<RenderTextureComponent>();

		m_pScoreText.first = title->AddComponent<TextComponent>();
		m_pScoreText.first->SetFont("Fonts/Joystix.otf", m_FontSize);

		auto scene{ SceneManager::GetInstance().GetActiveScene() };
		scene->Add(title);
	}

	void ScoreDisplayComponent::CreateScoreText()
	{
		auto score{ std::make_shared<GameObject>() };
		m_pTransforms.second = score->AddComponent<TransformComponent>();

		score->AddComponent<RenderTextureComponent>();

		m_pScoreText.second = score->AddComponent<TextComponent>();
		m_pScoreText.second->SetFont("Fonts/Joystix.otf", m_FontSize);
		m_pScoreText.second->SetColor(SDL_Color{ 255, 255, 255, 255 });

		auto scene{ SceneManager::GetInstance().GetActiveScene() };
		scene->Add(score);
	}
}
