#pragma once
#include "Component.h"

namespace dae
{
	class RenderComponent : public Component
	{
	public:
		explicit RenderComponent(GameObject* pOwner);
		~RenderComponent() override = default;

		RenderComponent(const RenderComponent& other) = delete;
		RenderComponent(RenderComponent&& other) noexcept = delete;
		RenderComponent& operator=(const RenderComponent& other) = delete;
		RenderComponent& operator=(RenderComponent&& other) noexcept = delete;

		virtual void Render() = 0;

		bool IsEnabled() const { return m_IsEnabled; }
		void SetEnabled(bool enable) { m_IsEnabled = enable; }
	private:
		bool m_IsEnabled{ true };
	};
}
