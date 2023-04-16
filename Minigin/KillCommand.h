#pragma once
#include "Command.h"

namespace dae
{
	class HealthComponent;

	class KillCommand final : public Command
	{
	public:
		explicit KillCommand(HealthComponent* health);
		~KillCommand() override = default;

		KillCommand(const KillCommand& other) = delete;
		KillCommand(KillCommand&& other) noexcept = delete;
		KillCommand& operator=(const KillCommand& other) = delete;
		KillCommand& operator=(KillCommand&& other) noexcept = delete;

		void Execute() override;
	private:
		HealthComponent* m_pHealthComponent{ nullptr };
	};
};
