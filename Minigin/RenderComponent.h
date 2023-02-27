#pragma once
#include "Component.h"
#include "Texture2D.h"
#include <memory>
#include <string>

namespace dae
{
	class RenderComponent final : public Component
	{
	public:
		explicit RenderComponent(const GameObject* pOwner);
		~RenderComponent() override = default;

		RenderComponent(const RenderComponent& other) = delete;
		RenderComponent(RenderComponent&& other) noexcept = delete;
		RenderComponent& operator=(const RenderComponent& other) = delete;
		RenderComponent& operator=(RenderComponent&& other) noexcept = delete;

		void Update() override;
		void Render() const;

		void SetTexture(const std::string& filename);
	private:
		std::shared_ptr<Texture2D> m_Texture{};
	};
}

