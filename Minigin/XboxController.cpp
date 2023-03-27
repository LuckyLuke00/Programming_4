#pragma once
#include "XboxController.h"
#include "InputManager.h"
#include <Windows.h>
#include <Xinput.h>

namespace dae
{
	class XboxController::Impl final
	{
	public:
		explicit Impl(unsigned int controllerIndex) :
			m_ControllerIndex{ controllerIndex }
		{}

		void Update()
		{
			CopyMemory(&m_PreviousState, &m_CurrentState, sizeof(XINPUT_STATE));
			ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
			XInputGetState(m_ControllerIndex, &m_CurrentState);

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

		void AddCommand(std::unique_ptr<Command> command, InputState inputState, XboxButton button)
		{
			m_ControllerCommands.emplace(std::make_pair(std::make_pair(inputState, button), std::move(command)));
		}

	private:
		using ControllerKey = std::pair<InputState, XboxController::XboxButton>;
		using ControllerCommandsMap = std::map<ControllerKey, std::unique_ptr<Command>>;
		ControllerCommandsMap m_ControllerCommands{};

		const unsigned int m_ControllerIndex{ 0 };

		unsigned int m_ButtonPressedThisFrame{ 0 };
		unsigned int m_ButtonReleasedThisFrame{ 0 };

		XINPUT_STATE m_CurrentState{ 0 };
		XINPUT_STATE m_PreviousState{ 0 };

		bool IsDownThisFrame(XboxButton button) const
		{
			return m_ButtonPressedThisFrame & static_cast<unsigned int>(button);
		}

		bool IsUpThisFrame(XboxButton button) const
		{
			return m_ButtonReleasedThisFrame & static_cast<unsigned int>(button);
		}

		bool IsPressed(XboxButton button) const
		{
			return m_CurrentState.Gamepad.wButtons & static_cast<unsigned int>(button);
		}
	};

	XboxController::XboxController(unsigned int controllerIndex) :
		m_pImpl{ new Impl{ controllerIndex } }
	{}

	XboxController::~XboxController()
	{
		delete m_pImpl;
		m_pImpl = nullptr;
	}

	void XboxController::Update()
	{
		m_pImpl->Update();
	}

	void XboxController::AddCommand(std::unique_ptr<Command> command, InputState inputState, XboxButton button)
	{
		m_pImpl->AddCommand(std::move(command), inputState, button);
	}
}
