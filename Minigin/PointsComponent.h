#pragma once
#include "Component.h"
#include "Subject.h"
#include "EventManager.h"

// TODO: Remove the need for this component, the points should be stored on the display
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

		void AddPoints(int points);
		void RemovePoints(int points);

		void SetPoints(int points);

		int GetPoints() const { return m_CurrentPoints; }
	private:
		int m_CurrentPoints{ 0 };
		Event m_PointsUpdatedEvent{ "PointsUpdated" };

		void ClampPoints();
	};
}
