#pragma once
#include "Component.h"
#include <memory>
#include <SDL_ttf.h>
#include <string>
#include <glm/vec2.hpp>

namespace dae
{
	class Font;
	class RenderTextureComponent;

	class TextComponent final : public Component
	{
	public:
		explicit TextComponent(GameObject* pOwner);
		~TextComponent() override = default;

		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) noexcept = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) noexcept = delete;

		void Update() override;

		void SetColor(const SDL_Color& color) { m_Color = color; }
		void SetFont(const std::string& file, unsigned int size);
		void SetText(const std::string& text);

		glm::vec2 GetTextSize() const;
	private:
		bool m_NeedsUpdate{ false };
		RenderTextureComponent* m_pRenderComponent{ nullptr };
		SDL_Color m_Color{ 255, 255, 255 };
		std::shared_ptr<Font> m_Font{ nullptr };
		std::string m_Text{ "" };
	};
}
