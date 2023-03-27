#include "Keyboard.h"
#include "InputManager.h"

namespace dae
{
	void Keyboard::Update(const SDL_Event& event)
	{
		// Check if the event is a key event
		if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
		{
			// Check if the key is in the map
			const auto it{ m_Commands.find(std::make_pair(event.type == SDL_KEYDOWN ? dae::InputState::Down : dae::InputState::Up, event.key.keysym.scancode)) };
			if (it != m_Commands.end())
			{
				// Execute the command
				it->second->Execute();
				return;
			}
		}

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
