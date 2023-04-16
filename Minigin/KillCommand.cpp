#include "KillCommand.h"
#include "HealthComponent.h"
#include "AddPointsCommand.h"

namespace dae
{
	KillCommand::KillCommand(HealthComponent* health) :
		m_pHealthComponent{ health }
	{}

	void KillCommand::Execute()
	{
		if (!m_pHealthComponent) return;
		m_pHealthComponent->Kill();
	}
}
