#include <SDL.h>
#include "InputManager.h"
#include <backends/imgui_impl_sdl2.h>

bool dae::InputManager::ProcessInput()
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT)
		{
			return false;
		}

		//process event for IMGUI
		ImGui_ImplSDL2_ProcessEvent(&e);
	}

	m_Keyboard.Update(e);

	return true;
}

void dae::InputManager::AddCommand(std::unique_ptr<Command> command, dae::Keyboard::InputState inputState, SDL_Scancode keyCode)
{
	m_Keyboard.AddCommand(std::move(command), inputState, keyCode);
}
