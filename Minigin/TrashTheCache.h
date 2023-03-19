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
		const int arraySize{ 1 << 25 };

		bool m_EX1Running{ false };
		bool m_EX2Running{ false };
		bool m_EX2AltRunning{ false };

		int m_SamplesEX1{ 10 };
		int m_SamplesEX2{ 100 };
		int m_MaxStep{ 1024 };

		std::vector<float> m_XValues{};
		std::vector<float> m_YValuesEX1{};
		std::vector<float> m_YValuesEX2{};
		std::vector<float> m_YValuesEX2Alt{};

		ImGui::PlotConfig m_PlotConfigEX1{};
		ImGui::PlotConfig m_PlotConfigEX2{};
		ImGui::PlotConfig m_PlotConfigEX2Alt{};
		ImGui::PlotConfig m_PlotConfigEX2Combined{};

		void EX1();
		void EX2();
		void EX2Alt();

		void GeneratePlot(ImGui::PlotConfig& plot, const std::vector<float>& data, std::vector<ImU32> colors = {});
	};
}
