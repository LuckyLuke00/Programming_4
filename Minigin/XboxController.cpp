#include "XboxController.h"
#include <iostream>
#include "InputManager.h"

namespace dae
{
	XboxController::XboxController(unsigned int controllerIndex) :
		m_ControllerIndex{ controllerIndex }
	{}

	void XboxController::Update()
	{
		CopyMemory(&m_PreviousState, &m_CurrentState, sizeof(XINPUT_STATE));
		ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
		XInputGetState(m_ControllerIndex, &m_CurrentState);
		std::cout << "Controller " << m_ControllerIndex << " connected: " << (m_CurrentState.dwPacketNumber != 0) << '\n';

		auto buttonChanges{ m_CurrentState.Gamepad.wButtons ^ m_PreviousState.Gamepad.wButtons };
		m_ButtonPressedThisFrame = buttonChanges & m_CurrentState.Gamepad.wButtons;
		m_ButtonReleasedThisFrame = buttonChanges & ~(m_PreviousState.Gamepad.wButtons);

		for (const auto& command : m_ControllerCommands)
		{
			switch (command.first.first)
			{
			case dae::InputState::Up:
				if (IsUpThisFrame(command.first.second))
				{
					command.second->Execute();
				}
				break;
			case dae::InputState::Down:
				if (IsDownThisFrame(command.first.second))
				{
					command.second->Execute();
				}
				break;

			case dae::InputState::Pressed:
				if (IsPressed(command.first.second))
				{
					command.second->Execute();
				}
				break;
			}
		}
	}

	void XboxController::AddCommand(std::unique_ptr<Command> command, InputState inputState, XboxButton button)
	{
		m_ControllerCommands.emplace(std::make_pair(std::make_pair(inputState, button), std::move(command)));
	}

	bool XboxController::IsDownThisFrame(XboxButton button) const
	{
		return m_ButtonPressedThisFrame & static_cast<unsigned int>(button);
	}

	bool XboxController::IsUpThisFrame(XboxButton button) const
	{
		return m_ButtonReleasedThisFrame & static_cast<unsigned int>(button);
	}

	bool XboxController::IsPressed(XboxButton button) const
	{
		return m_CurrentState.Gamepad.wButtons & static_cast<unsigned int>(button);
	}
}
