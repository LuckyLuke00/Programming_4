#include "Keyboard.h"
#include "InputManager.h"

namespace dae
{
	void Keyboard::Update()
	{
		// For holding keys
		const Uint8* state{ SDL_GetKeyboardState(nullptr) };
		for (const auto& [key, command] : m_Commands)
		{
			switch (key.first)
			{
			case InputState::Down:
				if (state[key.second])
				{
					command->Execute();
				}
				break;
			case InputState::Up:
				if (!state[key.second])
				{
					command->Execute();
				}
				break;
			case InputState::Pressed:
				if (state[key.second] && !m_KeysDown[key.second])
				{
					command->Execute();
				}
				break;
			case InputState::Released:
				if (!state[key.second] && m_KeysDown[key.second])
				{
					command->Execute();
				}
				break;
			}
		}

		// Update keys down state
		for (int i = 0; i < SDL_NUM_SCANCODES; ++i)
		{
			m_KeysDown[i] = state[i];
		}
	}

	void Keyboard::AddCommand(std::unique_ptr<Command> command, dae::InputState inputState, SDL_Scancode keyCode)
	{
		if (!command) return;
		m_Commands.emplace(std::make_pair(std::make_pair(inputState, keyCode), std::move(command)));
	}
}
