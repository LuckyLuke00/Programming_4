#pragma once
#include "Component.h"
#include <SDL_ttf.h>
#include <memory>
#include <string>

namespace dae
{
	class Font;
	class RenderComponent;

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
		void FixedUpdate() override {};
		void LateUpdate() override {};

		void SetColor(const SDL_Color& color) { m_Color = color; }
		void SetFont(const std::string& file, unsigned int size);
		void SetText(const std::string& text);
	private:
		bool m_NeedsUpdate{ false };
		RenderComponent* m_pRenderComponent{ nullptr };
		SDL_Color m_Color{ 255, 255, 255 };
		std::shared_ptr<Font> m_Font{ nullptr };
		std::string m_Text{ ' ' };
	};
}
