#include "KillCommand.h"
#include "HealthComponent.h"

dae::KillCommand::KillCommand(HealthComponent* health) :
	m_pHealthComponent{ health }
{}

void dae::KillCommand::Execute()
{
	if (!m_pHealthComponent) return;
	m_pHealthComponent->Kill();
}
