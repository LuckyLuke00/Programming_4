#pragma once
#include "Command.h"
#include <map>
#include <memory>
#include <SDL.h>
#include <array>

namespace dae
{
	enum class InputState;
	class Keyboard final
	{
	public:
		explicit Keyboard() = default;
		~Keyboard() = default;

		Keyboard(const Keyboard& other) = delete;
		Keyboard(Keyboard&& other) noexcept = delete;
		Keyboard& operator=(const Keyboard& other) = delete;
		Keyboard& operator=(Keyboard&& other) noexcept = delete;

		void Update();

		void AddCommand(std::unique_ptr<Command> command, InputState inputState, SDL_Scancode keyCode);

	private:

		// Store the commands in a map
		std::map<std::pair<InputState, SDL_Scancode>, std::unique_ptr<Command>> m_Commands{};

		// Keep track of the state of each key
		std::array<bool, SDL_NUM_SCANCODES> m_KeysDown{};
	};
}
