#pragma once
#include "Keyboard.h"
#include "Singleton.h"
#include "XboxController.h"
#include <vector>

namespace dae
{
	enum class InputState
	{
		Down,
		Up,
		Pressed,
		Released
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:

		bool ProcessInput();

		// Function to add a controller
		XboxController* AddXboxController();

		// Getter for the keyboard
		Keyboard& GetKeyboard() { return m_Keyboard; }
		const std::vector<std::unique_ptr<XboxController>>& GetControllers() const { return m_Controllers; }
	private:
		Keyboard m_Keyboard{};
		std::vector<std::unique_ptr<XboxController>> m_Controllers{};
	};
}
