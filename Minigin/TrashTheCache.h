#pragma once
#include "Component.h"
#include "RenderComponent.h"
#include <imgui_plot.h>
#include <vector>

namespace dae
{
	class TrashTheCache final : public RenderComponent
	{
	public:
		explicit TrashTheCache(GameObject* pOwner);
		~TrashTheCache() override = default;

		TrashTheCache(const TrashTheCache& other) = delete;
		TrashTheCache(TrashTheCache&& other) noexcept = delete;
		TrashTheCache& operator=(const TrashTheCache& other) = delete;
		TrashTheCache& operator=(TrashTheCache&& other) noexcept = delete;

		void Update() override;
		void Render() override;
	private:
		bool m_EX1Running{ false };
		int m_SamplesEX1{ 10 };
		int m_SamplesEX2{ 100 };
		int m_MaxStep{ 1024 };

		std::vector<float> m_XValues{};
		std::vector<float> m_YValuesEX1{};

		ImGui::PlotConfig m_PlotConfigEX1{};
		ImGui::PlotConfig m_PlotConfigEX2{};
		ImGui::PlotConfig m_PlotConfigEX2Alt{};
		ImGui::PlotConfig m_PlotConfigEX2Combined{};

		void EX1();

		void GeneratePlot(ImGui::PlotConfig& plot, const std::vector<float>& data, std::vector<ImU32> colors = {});
	};
}
