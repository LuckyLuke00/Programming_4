#include "AddPointsCommand.h"
#include "PointsComponent.h"

namespace dae
{
	AddPointsCommand::AddPointsCommand(PointsComponent* pointsComponent, int pointsToAdd) :
		m_pPointsComponent{ pointsComponent },
		m_PointsToAdd{ pointsToAdd }
	{}

	void AddPointsCommand::Execute()
	{
		if (!m_pPointsComponent) return;
		m_pPointsComponent->AddPoints(m_PointsToAdd);
	}
}
