#pragma once
#include "Component.h"
#include "Subject.h"

namespace dae
{
	class PointsComponent final : public Component, public Subject<int>
	{
	public:
		explicit PointsComponent(GameObject* pOwner);
		~PointsComponent() override = default;

		PointsComponent(const PointsComponent& other) = delete;
		PointsComponent(PointsComponent&& other) noexcept = delete;
		PointsComponent& operator=(const PointsComponent& other) = delete;
		PointsComponent& operator=(PointsComponent&& other) noexcept = delete;

		void AddPoints(int points) { m_CurrentPoints += points; ClampPoints(); Notify(m_CurrentPoints); }
		void RemovePoints(int points) { m_CurrentPoints -= points; ClampPoints(); Notify(m_CurrentPoints); }

		void SetPoints(int points) { m_CurrentPoints = points; ClampPoints(); Notify(m_CurrentPoints); }

		int GetPoints() const { return m_CurrentPoints; }
	private:
		int m_CurrentPoints{ 0 };

		void ClampPoints();
	};
}
