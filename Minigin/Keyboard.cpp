#include "Keyboard.h"
#include "InputManager.h"

namespace dae
{
	void Keyboard::Update()
	{
		// TODO: maybe fix this by checking for a KEY_UP event. This way we can also check for holding keys, This wont work when unfocussed
		// Don't use events

		// For holding keys
		const Uint8* state{ SDL_GetKeyboardState(nullptr) };
		for (const auto& [key, command] : m_Commands)
		{
			if (state[key.second] == (key.first == dae::InputState::Down))
			{
				command->Execute();
			}
		}
	}

	void Keyboard::AddCommand(std::unique_ptr<Command> command, dae::InputState inputState, SDL_Scancode keyCode)
	{
		m_Commands.emplace(std::make_pair(std::make_pair(inputState, keyCode), std::move(command)));
	}
}
