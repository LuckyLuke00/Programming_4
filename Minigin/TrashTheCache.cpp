#include "TrashTheCache.h"
#include "GameObject.h"
#include "RenderComponent.h"
#include <algorithm>
#include <imgui.h>
#include <chrono>
#include <iostream>

namespace dae
{
	struct Transform
	{
		float matrix[16]
		{
			1.f, .0f, .0f, .0f,
			.0f, 1.f, .0f, .0f,
			.0f, .0f, 1.f, .0f,
			.0f, .0f, .0f, 1.f
		};
	};

	class GameObject3D
	{
	public:
		Transform transform{};
		int ID{};
	};

	class GameObject3DAlt
	{
	public:
		Transform transform{};
		int ID{};
	};

	TrashTheCache::TrashTheCache(GameObject* pOwner)
		: RenderComponent{ pOwner }
	{
		for (int step{ 1 }; step <= m_MaxStep; step *= 2)
			m_XValues.emplace_back(static_cast<float>(step));
	}

	void TrashTheCache::Update()
	{
		// Clamp the values to a minimum of 3, because the highest and lowest values are always removed
		m_SamplesEX1 = std::max(m_SamplesEX1, 3);
		m_SamplesEX2 = std::max(m_SamplesEX2, 3);

		if (m_EX1Running)
		{
			EX1();
			m_EX1Running = false;
		}

		if (m_EX2Running)
		{
			EX2();
			m_EX2Running = false;
		}

		if (m_EX2AltRunning)
		{
			EX2Alt();
			m_EX2AltRunning = false;
		}

		if (m_RecalculateCombined && !m_YValuesEX2.empty() && !m_YValuesEX2Alt.empty())
		{
			EX2Combined();
			m_RecalculateCombined = false;
		}
	}

	void TrashTheCache::Render()
	{
		// EX1
		ImGui::Begin("Exercise 1");
		ImGui::InputInt("# samples", &m_SamplesEX1, 1);

		if (ImGui::Button("Trash the cache"))
		{
			m_EX1Running = true;
			ImGui::Text("Wait for it...");
		}

		ImGui::Plot("plotEX1", m_PlotConfigEX1);

		ImGui::End();

		// EX2
		ImGui::Begin("Exercise 2");
		ImGui::InputInt("# samples", &m_SamplesEX2, 1);

		if (ImGui::Button("Trash the cache with GameObject3D"))
		{
			m_EX2Running = true;
			ImGui::Text("Wait for it...");
			m_RecalculateCombined = true;
		}

		ImGui::Plot("plotEX2", m_PlotConfigEX2);

		if (ImGui::Button("Trash the cache with GameObject3DAlt"))
		{
			m_EX2AltRunning = true;
			ImGui::Text("Wait for it...");
			m_RecalculateCombined = true;
		}

		ImGui::Plot("plotEX2Alt", m_PlotConfigEX2Alt);

		if (!m_YValuesEX2.empty() && !m_YValuesEX2Alt.empty())
		{
			ImGui::Text("Combined:");
			ImGui::Plot("plotEX2Combined", m_PlotConfigEX2Combined);
		}

		ImGui::End();
	}

	void TrashTheCache::EX1()
	{
		// Clear the vector
		m_YValuesEX1.clear();
		m_YValuesEX1.reserve(m_XValues.size());

		auto* arr{ new int[m_ArraySize] };

		// Fill the array
		for (int i{ 0 }; i < m_ArraySize; ++i) arr[i] = 1;

		// Iterate over the buffer in steps of 1, 2, 4, 8 and so on till m_MaxStep
		for (int step{ 1 }; step <= m_MaxStep; step *= 2)
		{
			long long lowestTime{ LONG_MAX };
			long long highestTime{ 0 };

			long long timeSum{ 0 };
			for (int i{ 0 }; i < m_SamplesEX1; ++i)
			{
				const auto start{ std::chrono::high_resolution_clock::now() };

				for (int j{ 0 }; j < m_ArraySize; j += step)
				{
					arr[j] *= 2;
				}

				const auto end{ std::chrono::high_resolution_clock::now() };
				const auto total{ std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() };
				timeSum += total;

				// Find the lowest and highest time
				lowestTime = std::min(lowestTime, total);
				highestTime = std::max(highestTime, total);
			}

			// Remove the highest and lowest time
			timeSum -= lowestTime + highestTime;

			// Add the average time to the plot
			m_YValuesEX1.emplace_back(static_cast<float>(timeSum / (m_SamplesEX1 - 2)) / 1000.f);
		}

		// Clean up the buffer
		delete[] arr;
		arr = nullptr;

		// Generate the plot
		GeneratePlot(m_PlotConfigEX1, m_YValuesEX1);
	}

	void TrashTheCache::EX2()
	{
		// Clear the vector
		m_YValuesEX2.clear();
		m_YValuesEX2.reserve(m_XValues.size());

		auto* arr{ new GameObject3D[m_ArraySize] };

		// Fill the array
		for (int i{ 0 }; i < m_ArraySize; ++i) arr[i].ID = 1;

		// Iterate over the buffer in steps of 1, 2, 4, 8 and so on till m_MaxStep
		for (int step{ 1 }; step <= m_MaxStep; step *= 2)
		{
			long long lowestTime{ LONG_MAX };
			long long highestTime{ 0 };

			long long timeSum{ 0 };
			for (int i{ 0 }; i < m_SamplesEX2; ++i)
			{
				const auto start{ std::chrono::high_resolution_clock::now() };

				for (int j{ 0 }; j < m_ArraySize; j += step)
				{
					arr[j].ID *= 2;
				}

				const auto end{ std::chrono::high_resolution_clock::now() };
				const auto total{ std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() };
				timeSum += total;

				// Find the lowest and highest time
				lowestTime = std::min(lowestTime, total);
				highestTime = std::max(highestTime, total);
			}

			// Remove the highest and lowest time
			timeSum -= lowestTime + highestTime;

			// Add the average time to the plot
			m_YValuesEX2.emplace_back(static_cast<float>(timeSum / (m_SamplesEX2 - 2)) / 1000.f);
		}
		// Clean up the buffer
		delete[] arr;
		arr = nullptr;

		// Generate the plot
		GeneratePlot(m_PlotConfigEX2, m_YValuesEX2, ImColor(130, 201, 30));
	}

	void TrashTheCache::EX2Alt()
	{
		// Clear the vector
		m_YValuesEX2Alt.clear();
		m_YValuesEX2Alt.reserve(m_XValues.size());

		auto* arr{ new GameObject3DAlt[m_ArraySize] };

		// Fill the array
		for (int i{ 0 }; i < m_ArraySize; ++i) arr[i].ID = 1;

		// Iterate over the buffer in steps of 1, 2, 4, 8 and so on till m_MaxStep
		for (int step{ 1 }; step <= m_MaxStep; step *= 2)
		{
			long long lowestTime{ LONG_MAX };
			long long highestTime{ 0 };

			long long timeSum{ 0 };
			for (int i{ 0 }; i < m_SamplesEX2; ++i)
			{
				const auto start{ std::chrono::high_resolution_clock::now() };

				for (int j{ 0 }; j < m_ArraySize; j += step)
				{
					arr[j].ID *= 2;
				}

				const auto end{ std::chrono::high_resolution_clock::now() };
				const auto total{ std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() };
				timeSum += total;

				// Find the lowest and highest time
				lowestTime = std::min(lowestTime, total);
				highestTime = std::max(highestTime, total);
			}

			// Remove the highest and lowest time
			timeSum -= lowestTime + highestTime;

			// Add the average time to the plot
			m_YValuesEX2Alt.emplace_back(static_cast<float>(timeSum / (m_SamplesEX2 - 2)) / 1000.f);
		}
		// Clean up the buffer
		delete[] arr;
		arr = nullptr;

		// Generate the plot
		GeneratePlot(m_PlotConfigEX2Alt, m_YValuesEX2Alt, ImColor(21, 170, 191));
	}

	void TrashTheCache::EX2Combined()
	{
		// Clear the vector
		m_YValuesEX2Combined.clear();

		// Combine the vectors
		m_YValuesEX2Combined.emplace_back(m_YValuesEX2.data());
		m_YValuesEX2Combined.emplace_back(m_YValuesEX2Alt.data());

		std::vector<ImU32> colors{ ImColor(130, 201, 30), ImColor(21, 170, 191) };

		// Generate the plot
		ImU32* pColors{ new ImU32[]{ ImColor(130, 201, 30), ImColor(21, 170, 191) } };
		GeneratePlot(m_PlotConfigEX2Combined, m_YValuesEX2Combined, pColors);

		delete[] pColors;
		pColors = nullptr;
	}

	void TrashTheCache::GeneratePlot(ImGui::PlotConfig& plot, const std::vector<float>& data, const ImU32& color)
	{
		// Plot defaults
		plot.grid_y.show = true;
		plot.grid_y.size = 5.f;
		plot.grid_y.subticks = 1;
		plot.line_thickness = 2.f;
		plot.scale.min = .0f;
		plot.tooltip.format = "x%.2f, y%.2f";
		plot.tooltip.show = true;

		// Generated plot values
		plot.values.count = static_cast<int>(data.size());
		plot.values.xs = m_XValues.data();
		plot.values.ys = data.data();
		plot.scale.max = std::ranges::max(data);
		plot.frame_size = ImVec2(150, 75);

		plot.values.color = color;
	}

	void TrashTheCache::GeneratePlot(ImGui::PlotConfig& plot, std::vector<const float*>& data, const ImU32* colors, const int lineAmount)
	{
		// Plot defaults
		plot.grid_y.show = true;
		plot.grid_y.size = 5.f;
		plot.grid_y.subticks = 1;
		plot.line_thickness = 2.f;
		plot.scale.min = .0f;
		plot.tooltip.format = "x%.2f, y%.2f";
		plot.tooltip.show = true;

		// Generated plot values
		plot.values.count = static_cast<int>(m_XValues.size());
		plot.values.xs = m_XValues.data();
		plot.scale.max = *std::ranges::max(data);
		plot.frame_size = ImVec2(150, 75);
		plot.values.ys_list = data.data();
		plot.values.ys_count = lineAmount;

		plot.values.colors = colors;
	}
}