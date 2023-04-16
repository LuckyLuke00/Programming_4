#include "PointsComponent.h"

namespace dae
{
	PointsComponent::PointsComponent(GameObject* pOwner) :
		Component{ pOwner }
	{}

	void PointsComponent::ClampPoints()
	{
		m_CurrentPoints = std::max(m_CurrentPoints, 0);
	}
}
