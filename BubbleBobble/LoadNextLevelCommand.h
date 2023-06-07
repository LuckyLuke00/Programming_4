#pragma once
#include "Command.h"

namespace dae
{
	class LoadNextLevelCommand final : public Command
	{
	public:
		explicit LoadNextLevelCommand() = default;
		~LoadNextLevelCommand() override = default;

		LoadNextLevelCommand(const LoadNextLevelCommand& other) = delete;
		LoadNextLevelCommand(LoadNextLevelCommand&& other) noexcept = delete;
		LoadNextLevelCommand& operator=(const LoadNextLevelCommand& other) = delete;
		LoadNextLevelCommand& operator=(LoadNextLevelCommand&& other) noexcept = delete;

		void Execute() override;
		void Undo() override;
	};
}
