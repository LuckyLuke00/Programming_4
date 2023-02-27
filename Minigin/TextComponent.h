#pragma once
#include "Component.h"
#include <SDL_ttf.h>
#include <memory>
#include <string>


namespace dae
{
	class Font;

	class TextComponent final : public Component
	{
	public:
		explicit TextComponent(const GameObject* pOwner);
		~TextComponent() override = default;

		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) noexcept = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) noexcept = delete;

		void Update() override;

		void SetColor(const SDL_Color& color) { m_Color = color; }
		void SetFont(const std::string& file, unsigned int size);
		void SetText(const std::string& text);
	private:
		bool m_NeedsUpdate{ false };
		SDL_Color m_Color{ 255, 255, 255 };
		std::string m_Text{};
		std::shared_ptr<Font> m_Font{ nullptr };
	};
}

