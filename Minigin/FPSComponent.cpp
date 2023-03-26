#include "FPSComponent.h"
#include "GameObject.h"
#include "TextComponent.h"
#include "Time.h"

namespace dae
{
	FPSComponent::FPSComponent(GameObject* pOwner) :
		Component{ pOwner },
		m_pTextComponent{ pOwner->GetComponent<TextComponent>() }
	{}

	void FPSComponent::Update()
	{
		m_FPSTimer += Time::GetDeltaSeconds();

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
		m_FPS = static_cast<int>(1.f / Time::GetDeltaSeconds() + .5f);
	}
}
