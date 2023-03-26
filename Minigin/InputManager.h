#pragma once
#include "Singleton.h"
#include "Keyboard.h"

namespace dae
{
	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();
		void AddCommand(std::unique_ptr<Command> command, dae::Keyboard::InputState inputState, SDL_Scancode keyCode);

		// Getter for the keyboard
		Keyboard& GetKeyboard() { return m_Keyboard; }
	private:
		Keyboard m_Keyboard{};
	};
}
