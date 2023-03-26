#pragma once
namespace dae
{
	class XboxController final
	{
		explicit XboxController() = default;
		~XboxController() = default;

		XboxController(const XboxController& other) = delete;
		XboxController(XboxController&& other) noexcept = delete;
		XboxController& operator=(const XboxController& other) = delete;
		XboxController& operator=(XboxController&& other) noexcept = delete;
	};
}
