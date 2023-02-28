#include "FPSComponent.h"
#include "GameObject.h"
#include "Time.h"
#include "TextComponent.h"
#include <format>

namespace dae
{
	FPSComponent::FPSComponent(const GameObject* pOwner)
		: Component{ pOwner }
	{
	}

	void FPSComponent::Update()
	{
		m_FPSTimer += Time::GetDeltaTime();
		++m_FPSCount;

		if (m_FPSTimer < m_FPSUpdateInterval) return;

		m_FPS = static_cast<int>(static_cast<float>(m_FPSCount) / m_FPSTimer);
		m_FPSTimer = .0f;
		m_FPSCount = 0;

		// Check if text component is already set
		if (!m_pTextComponent)
		{
			// Check if owner has text component, if not return
			if (!GetOwner()->HasComponent<TextComponent>()) return;

			// If owner has a text component, set it, this will only happen once
			m_pTextComponent = GetOwner()->GetComponent<TextComponent>();
		}

		m_pTextComponent->SetText(std::format("{} FPS", m_FPS));
	}
}
