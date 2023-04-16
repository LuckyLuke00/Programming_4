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

	void PointsComponent::AddPoints(int points)
	{
		m_CurrentPoints += points;
		ClampPoints();
		Notify(m_CurrentPoints);
		EventManager::GetInstance().Notify(&m_PointsUpdatedEvent, m_CurrentPoints);
	}

	void PointsComponent::RemovePoints(int points)
	{
		m_CurrentPoints -= points;
		ClampPoints();
		Notify(m_CurrentPoints);
		EventManager::GetInstance().Notify(&m_PointsUpdatedEvent, m_CurrentPoints);
	}

	void PointsComponent::SetPoints(int points)
	{
		m_CurrentPoints = points;
		ClampPoints();
		Notify(m_CurrentPoints);
		EventManager::GetInstance().Notify(&m_PointsUpdatedEvent, m_CurrentPoints);
	}
}
