#pragma once
#include "Component.h"

namespace dae
{
	class TextComponent;
	class FPSComponent final : public Component
	{
	public:
		explicit FPSComponent(const GameObject* pOwner);
		~FPSComponent() override = default;

		FPSComponent(const FPSComponent& other) = delete;
		FPSComponent(FPSComponent&& other) noexcept = delete;
		FPSComponent& operator=(const FPSComponent& other) = delete;
		FPSComponent& operator=(FPSComponent&& other) noexcept = delete;

		void Update() override;
		void FixedUpdate() override {};
		void LateUpdate() override {};

		unsigned int GetFPS() const { return m_FPS; }
	private:
		float m_FPSTimer{ .0f };
		float m_FPSUpdateInterval{ .25f };
		unsigned int m_FPS{ 0 };
		unsigned int m_FPSCount{ 0 };

		TextComponent* m_pTextComponent{ nullptr };

		void CalculateFPS();
	};
}
