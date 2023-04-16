#pragma once
#include "Observer.h"
#include "TextComponent.h"
#include "GameObject.h"

namespace dae
{
	template<typename T>
	class NumberDisplay : public Component, public Observer<T>
	{
	public:
		explicit NumberDisplay(GameObject* pOwner);
		~NumberDisplay() override = default;

		NumberDisplay(const NumberDisplay& other) = delete;
		NumberDisplay(NumberDisplay&& other) noexcept = delete;
		NumberDisplay& operator=(const NumberDisplay& other) = delete;
		NumberDisplay& operator=(NumberDisplay&& other) noexcept = delete;

		void OnNotify(const T& value) override;

		void SetPrefix(const char* text) { m_Text = text; UpdateText(); }
		void SetNumber(const T& value) { OnNotify(value); }

		// Getter for the observer
		Observer<T>* GetObserver() override { return this; }

	private:
		TextComponent* m_pTextComponent{ nullptr };

		T m_Value = T{};
		const char* m_Text{ "" };

		void UpdateText();
	};

	template<typename T>
	inline NumberDisplay<T>::NumberDisplay(GameObject* pOwner) :
		Component{ pOwner },
		m_pTextComponent{ pOwner->GetComponent<TextComponent>() }
	{}

	template<typename T>
	inline void NumberDisplay<T>::OnNotify(const T& value)
	{
		m_Value = value;
		UpdateText();
	}
	template<typename T>
	inline void NumberDisplay<T>::UpdateText()
	{
		m_pTextComponent->SetText(m_Text + std::to_string(m_Value));
	}
}
