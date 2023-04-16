#include "HealthComponent.h"

namespace dae
{
	HealthComponent::HealthComponent(GameObject* pOwner) :
		Component{ pOwner }
	{}
	
	void HealthComponent::ClampLives()
	{
		m_CurrentLives =  std::max(std::min(m_CurrentLives, m_MaxLives), 0);

	}
}
