#pragma once
#include "Command.h"

namespace dae
{
	class PointsComponent;

	class AddPointsCommand final : public Command
	{
	public:
		explicit AddPointsCommand(PointsComponent* pointsComponent, int pointsToAdd);
		~AddPointsCommand() override = default;

		AddPointsCommand(const AddPointsCommand& other) = delete;
		AddPointsCommand(AddPointsCommand&& other) noexcept = delete;
		AddPointsCommand& operator=(const AddPointsCommand& other) = delete;
		AddPointsCommand& operator=(AddPointsCommand&& other) noexcept = delete;

		void Execute() override;
	private:
		PointsComponent* m_pPointsComponent{ nullptr };
		int m_PointsToAdd{ 0 };
	};
};
