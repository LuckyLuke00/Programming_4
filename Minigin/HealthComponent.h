#pragma once
#include "Component.h"
#include "Subject.h"

namespace dae
{
	class HealthComponent final : public Component, public Subject<int>
	{
	public:
		explicit HealthComponent(GameObject* pOwner);
		~HealthComponent() override = default;

		HealthComponent(const HealthComponent& other) = delete;
		HealthComponent(HealthComponent&& other) noexcept = delete;
		HealthComponent& operator=(const HealthComponent& other) = delete;
		HealthComponent& operator=(HealthComponent&& other) noexcept = delete;

		void AddLives(int lives) { m_CurrentLives += lives; ClampLives(); Notify(m_CurrentLives); }
		void RemoveLives(int lives) { m_CurrentLives -= lives; ClampLives(); Notify(m_CurrentLives); }

		void Kill() { RemoveLives(1); }

		void SetMaxLives(int maxLives) { m_MaxLives = maxLives; }

		int GetLives() const { return m_CurrentLives; }
		int GetMaxLives() const { return m_MaxLives; }
	private:
		int m_MaxLives{ 3 };
		int m_CurrentLives{ m_MaxLives };

		void ClampLives();
	};
}
