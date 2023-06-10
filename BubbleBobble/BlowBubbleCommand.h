#pragma once
#include "Command.h"
#include <functional>

namespace dae
{
	class BlowBubbleCommand final : public Command
	{
	public:
		explicit BlowBubbleCommand(const std::function<void()>& blowBubbleFunction);
		~BlowBubbleCommand() override = default;

		BlowBubbleCommand(const BlowBubbleCommand& other) = delete;
		BlowBubbleCommand(BlowBubbleCommand&& other) noexcept = delete;
		BlowBubbleCommand& operator=(const BlowBubbleCommand& other) = delete;
		BlowBubbleCommand& operator=(BlowBubbleCommand&& other) noexcept = delete;

		void Execute() override;
	private:
		std::function<void()> m_BlowBubbleFunction;
	};
}
