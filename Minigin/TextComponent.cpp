#include "TextComponent.h"
#include "Font.h"
#include "GameObject.h"
#include "RenderTextureComponent.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <stdexcept>

namespace dae
{
	TextComponent::TextComponent(GameObject* pOwner) :
		Component{ pOwner },
		m_pRenderComponent{ pOwner->GetComponent<RenderTextureComponent>() }
	{
	}

	void TextComponent::Update()
	{
		if (!m_NeedsUpdate) return;

		if (!m_pRenderComponent)
		{
			throw std::runtime_error(std::string("TextComponent::Update() > GameObject does not have a RenderTextureComponent!"));
		}

		const auto surf{ TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), m_Color) };
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture{ SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf) };
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_pRenderComponent->SetTexture(std::make_shared<Texture2D>(texture));
		m_NeedsUpdate = false;
	}

	void TextComponent::SetText(const std::string& text)
	{
		m_Text = text;
		m_NeedsUpdate = true;
	}
	glm::vec2 TextComponent::GetTextSize() const
	{
		if (m_Text.empty()) return glm::vec2{ 0, 0 };

		int width{};
		int height{};
		TTF_SizeText(m_Font->GetFont(), m_Text.c_str(), &width, &height);
		return glm::vec2{ width, height };
	}

	void TextComponent::SetFont(const std::string& file, unsigned int size)
	{
		m_Font = ResourceManager::GetInstance().LoadFont(file, size);
		m_NeedsUpdate = true;
	}
}
