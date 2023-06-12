#pragma once
#include "Command.h"

namespace dae
{
	class MuteCommand final : public Command
	{
	public:
		explicit MuteCommand() = default;
		~MuteCommand() override = default;

		MuteCommand(const MuteCommand& other) = delete;
		MuteCommand(MuteCommand&& other) noexcept = delete;
		MuteCommand& operator=(const MuteCommand& other) = delete;
		MuteCommand& operator=(MuteCommand&& other) noexcept = delete;
	private:
		bool m_IsMuted{ false };

		void Execute() override;
	};
}
