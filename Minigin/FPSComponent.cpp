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
		m_pTextComponent = GetOwner()->GetComponent<TextComponent>();
	}

	void FPSComponent::Update()
	{
		m_FPSTimer += Time::GetDeltaTime();

		if (m_FPSTimer < m_FPSUpdateInterval) return;
		m_FPSTimer = .0f;

		CalculateFPS();

		if (!m_pTextComponent)
		{
			throw std::runtime_error(std::string("FPSComponent::Update() > GameObject does not have a TextComponent!"));
		}

		m_pTextComponent->SetText(std::format("{} FPS", m_FPS));
	}

	void FPSComponent::CalculateFPS()
	{
		m_FPS = static_cast<int>(1.f / Time::GetDeltaTime() + .5f);
	}
}
