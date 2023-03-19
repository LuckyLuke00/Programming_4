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
		Transform* transform;
		int ID;
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
	}

	void TrashTheCache::Render()
	{
		ImGui::Begin("Exercise 1"); //begin for window Exercise 1
		ImGui::InputInt("# samples", &m_SamplesEX1, 1);

		if (ImGui::Button("Trash the cache"))
		{
			m_EX1Running = true;
			ImGui::Text("Wait for it...");
		}

		ImGui::Plot("plotEX1", m_PlotConfigEX1);

		ImGui::End(); //end for window Exercise 1
	}

	void TrashTheCache::EX1()
	{
		// Allocate a large buffer of integers (for example 2 ^ 26 integers) on the heap
		constexpr int size{ 1 << 26 };

		auto* arr{ new GameObject3D[size] };

		// Fill the array
		for (int i{ 0 }; i < size; ++i) arr[i].ID = 1;

		// Iterate over the buffer in steps of 1, 2, 4, 8 and so on till m_MaxStep
		for (int step{ 1 }; step <= m_MaxStep; step *= 2)
		{
			long long lowestTime{ LONG_MAX };
			long long highestTime{ 0 };

			long long timeSum{ 0 };
			for (int i{ 0 }; i < m_SamplesEX1; ++i)
			{
				const auto start{ std::chrono::high_resolution_clock::now() };

				for (int j{ 0 }; j < size; j += step)
				{
					arr[step].ID *= 2;
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

	void TrashTheCache::GeneratePlot(ImGui::PlotConfig& plot, const std::vector<float>& data, std::vector<ImU32> colors)
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
		m_PlotConfigEX1.scale.max = std::ranges::max(data);
		plot.frame_size = ImVec2(150, 75);

		if (colors.empty())
		{
			plot.values.color = ImColor(253, 126, 20);
		}
		else
		{
			plot.values.color = colors.front();
		}
	}
}