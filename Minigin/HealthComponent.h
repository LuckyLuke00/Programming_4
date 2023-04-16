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

		void AddHealth(int health) { m_CurrentHealth += health; ClampHealth(); Notify(m_CurrentHealth); }
		void RemoveHealth(int health) { m_CurrentHealth -= health; ClampHealth();  Notify(m_CurrentHealth); }

		void AddLives(int lives) { m_CurrentLives += lives; ClampLives(); Notify(m_CurrentLives); }
		void RemoveLives(int lives) { m_CurrentLives -= lives; ClampLives(); Notify(m_CurrentLives); }

		void SetMaxHealth(int maxHealth) { m_MaxHealth = maxHealth; }
		void SetMaxLives(int maxLives) { m_MaxLives = maxLives; }

		int GetHealth() const { return m_CurrentHealth; }
		int GetMaxHealth() const { return m_MaxHealth; }

		int GetLives() const { return m_CurrentLives; }
		int GetMaxLives() const { return m_MaxLives; }
	private:
		int m_MaxHealth{ 100 };
		int m_CurrentHealth{ m_MaxHealth };

		int m_MaxLives{ 3 };
		int m_CurrentLives{ m_MaxLives };

		void ClampLives();
		void ClampHealth();
	};
}
