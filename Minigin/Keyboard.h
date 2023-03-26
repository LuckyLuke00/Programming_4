#pragma once
#include "Command.h"
#include <map>
#include <memory>
#include <SDL.h>

namespace dae
{
	class Keyboard final
	{
	public:
		enum class InputState
		{
			Down,
			Up
		};

		explicit Keyboard() = default;
		~Keyboard() = default;

		Keyboard(const Keyboard& other) = delete;
		Keyboard(Keyboard&& other) noexcept = delete;
		Keyboard& operator=(const Keyboard& other) = delete;
		Keyboard& operator=(Keyboard&& other) noexcept = delete;

		void Update(const SDL_Event& event);

		void AddCommand(std::unique_ptr<Command> command, InputState inputState, SDL_Scancode keyCode);
	private:

		// Store the commands in a map
		std::map<std::pair<InputState, SDL_Scancode>, std::unique_ptr<Command>> m_Commands{};
	};
}
