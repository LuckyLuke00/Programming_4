#pragma once
#include "Component.h"

namespace dae
{
	class FPSComponent final : public Component
	{
	public:
		explicit FPSComponent(const GameObject* pOwner);
		~FPSComponent() override = default;

		FPSComponent(const FPSComponent& other) = delete;
		FPSComponent(FPSComponent&& other) noexcept = delete;
		FPSComponent& operator=(const FPSComponent& other) = delete;
		FPSComponent& operator=(FPSComponent&& other) noexcept = delete;

		void Update() override {};
		void FixedUpdate() override {};
		void LateUpdate() override {};

	private:
	};
}