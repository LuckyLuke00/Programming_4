#pragma once
#include "RenderComponent.h"
#include <string>
#include <memory>
#include "Texture2D.h"

namespace dae
{
	class TransformComponent;

	class RenderTextureComponent final : public RenderComponent
	{
	public:
		explicit RenderTextureComponent(GameObject* pOwner);
		~RenderTextureComponent() override = default;

		RenderTextureComponent(const RenderTextureComponent& other) = delete;
		RenderTextureComponent(RenderTextureComponent&& other) noexcept = delete;
		RenderTextureComponent& operator=(const RenderTextureComponent& other) = delete;
		RenderTextureComponent& operator=(RenderTextureComponent&& other) noexcept = delete;

		void Render() override;

		void SetTexture(const std::string& filename);
		void SetTexture(std::shared_ptr<Texture2D> texture) { m_Texture = texture; }

		// Getter for the texture size
		glm::vec2 GetTextureSize() const { return m_Texture.get()->GetSize(); }

	private:
		TransformComponent* m_pTransformComponent{ nullptr };
		std::shared_ptr<Texture2D> m_Texture{};
	};
}
