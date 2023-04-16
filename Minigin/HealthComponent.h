#pragma once
#include "Component.h"
#include "Subject.h"

namespace dae
{
	class HealthComponent final : public Component, public Subject<unsigned int>
	{
	public:
		explicit HealthComponent(GameObject* pOwner);
		~HealthComponent() override = default;

		HealthComponent(const HealthComponent& other) = delete;
		HealthComponent(HealthComponent&& other) noexcept = delete;
		HealthComponent& operator=(const HealthComponent& other) = delete;
		HealthComponent& operator=(HealthComponent&& other) noexcept = delete;

		void AddHealth(unsigned int health) { m_CurrentHealth += health; Notify(m_CurrentHealth); }
		void RemoveHealth(unsigned int health) { m_CurrentHealth -= health; Notify(m_CurrentHealth); }

		void AddLives(unsigned int lives) { m_CurrentLives += lives; Notify(m_CurrentLives); }
		void RemoveLives(unsigned int lives) { m_CurrentLives -= lives; Notify(m_CurrentLives); }

		void SetMaxHealth(unsigned int maxHealth) { m_MaxHealth = maxHealth; }
		void SetMaxLives(unsigned int maxLives) { m_MaxLives = maxLives; }

		unsigned int GetHealth() const { return m_CurrentHealth; }
		unsigned int GetMaxHealth() const { return m_MaxHealth; }

		unsigned int GetLives() const { return m_CurrentLives; }
		unsigned int GetMaxLives() const { return m_MaxLives; }
	private:
		unsigned int m_MaxHealth{ 100 };
		unsigned int m_CurrentHealth{ m_MaxHealth };

		unsigned int m_MaxLives{ 3 };
		unsigned int m_CurrentLives{ m_MaxLives };
	};
}
