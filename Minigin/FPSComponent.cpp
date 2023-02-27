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

		if (!m_pTextComponent || !GetOwner()->HasComponent<TextComponent>())
		{
			if (!GetOwner()->HasComponent<TextComponent>()) return;
			m_pTextComponent = GetOwner()->GetComponent<TextComponent>();
		}

		m_pTextComponent->SetText(std::format("{} FPS", m_FPS));
	}
}
