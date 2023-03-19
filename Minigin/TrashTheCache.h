#pragma once
#include "Component.h"
#include "RenderComponent.h"

namespace dae
{
	class TrashTheCache final : public RenderComponent
	{
	public:
		using RenderComponent::RenderComponent;
		~TrashTheCache() override = default;

		TrashTheCache(const TrashTheCache& other) = delete;
		TrashTheCache(TrashTheCache&& other) noexcept = delete;
		TrashTheCache& operator=(const TrashTheCache& other) = delete;
		TrashTheCache& operator=(TrashTheCache&& other) noexcept = delete;

		void Update() override;
		void Render() override;
	private:
		int m_SamplesEX1{ 10 };
		int m_SamplesEX2{ 100 };
	};
}
