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

	for (const auto& controller : m_Controllers)
	{
		controller->Update();
	}

	m_Keyboard.Update(e);

	return true;
}

dae::XboxController* dae::InputManager::AddXboxController()
{
	const unsigned int index{ static_cast<unsigned int>(m_Controllers.size()) };
	m_Controllers.emplace_back(std::make_unique<XboxController>(index));
	return m_Controllers.back().get();
}
