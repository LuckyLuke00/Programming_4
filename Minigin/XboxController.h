#pragma once
#include <Windows.h>
#include <Xinput.h>
#include <memory>
#include "Command.h"
#include <map>
namespace dae
{
	enum class InputState;
	class XboxController final
	{
	public:
		explicit XboxController(unsigned int controllerIndex);
		~XboxController() = default;

		XboxController(const XboxController& other) = delete;
		XboxController(XboxController&& other) noexcept = delete;
		XboxController& operator=(const XboxController& other) = delete;
		XboxController& operator=(XboxController&& other) noexcept = delete;

		enum class XboxButton : unsigned int
		{
			// D-Pad
			DPadUp = 0x0001,
			DPadDown = 0x0002,
			DPadLeft = 0x0004,
			DPadRight = 0x0008,

			// Start and Back
			Start = 0x0010,
			Back = 0x0020,

			// Thumb Stick buttons
			LeftThumb = 0x0040,
			RightThumb = 0x0080,

			// Shoulder buttons
			LeftShoulder = 0x0100,
			RightShoulder = 0x0200,

			// Face buttons
			A = 0x1000,
			B = 0x2000,
			X = 0x4000,
			Y = 0x8000,
		};

		void Update();
		void AddCommand(std::unique_ptr<Command> command, InputState inputstate, XboxButton button);
	private:
		using ControllerKey = std::pair<InputState, XboxController::XboxButton>;
		using ControllerCommandsMap = std::map<ControllerKey, std::unique_ptr<Command>>;
		ControllerCommandsMap m_ControllerCommands{};

		const unsigned int m_ControllerIndex{ 0 };

		unsigned int m_ButtonPressedThisFrame{ 0 };
		unsigned int m_ButtonReleasedThisFrame{ 0 };

		XINPUT_STATE m_CurrentState{ 0 };
		XINPUT_STATE m_PreviousState{ 0 };

		bool IsDownThisFrame(XboxButton button) const;
		bool IsUpThisFrame(XboxButton button) const;
		bool IsPressed(XboxButton button) const;
	};
}
