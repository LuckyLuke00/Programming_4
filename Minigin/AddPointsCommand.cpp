#include "AddPointsCommand.h"
#include "PointsComponent.h"

namespace dae
{
	// Only the points display should be able to add point
	// This command should not be used it should be
	// (I picked something up, and the points display should give the points based on that)
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
