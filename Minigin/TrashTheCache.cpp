#include "TrashTheCache.h"
#include "GameObject.h"
#include "RenderComponent.h"
#include <algorithm>
#include <imgui.h>

namespace dae
{
	void TrashTheCache::Update()
	{
		// Clamp the values to a minimum of 3, because the highest and lowest values are always removed
		m_SamplesEX1 = std::max(m_SamplesEX1, 3);
		m_SamplesEX2 = std::max(m_SamplesEX2, 3);
	}

	void TrashTheCache::Render()
	{
		ImGui::Begin("Exercise 1"); //begin for window Exercise 1
		//ImGui::InputInt("# samples", &m_SamplesEX1, 1);

		ImGui::End(); //end for window Exercise 1
	}
}