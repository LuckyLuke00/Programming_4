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

		m_FPS = m_FPSCount;
		m_FPSTimer = .0f;
		m_FPSCount = 0;

		// Check if the owner has a text component
		if (!GetOwner()->HasComponent<TextComponent>()) return;

		// Update the text component
		GetOwner()->GetComponent<TextComponent>()->SetText(std::format("{} FPS", m_FPS) );
	}
}