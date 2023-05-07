#include "RenderTextureComponent.h"
#include "GameObject.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "TransformComponent.h"
#include <stdexcept>

namespace dae
{
	RenderTextureComponent::RenderTextureComponent(GameObject* pOwner) :
		RenderComponent{ pOwner },
		m_pTransformComponent{ pOwner->GetComponent<TransformComponent>() }
	{}

	void RenderTextureComponent::Render()
	{
		if (!m_Texture) return;

		if (!m_pTransformComponent)
		{
			throw std::runtime_error(std::string("RenderComponent::Render() > GameObject does not have a TransformComponent!"));
		}

		const auto& pos{ m_pTransformComponent->GetWorldPosition() };
		// Calulate the width and height of the texture based on the scale of the transform
		const auto width{ m_Texture.get()->GetSize().x * m_pTransformComponent->GetScale() };
		const auto height{ m_Texture.get()->GetSize().y * m_pTransformComponent->GetScale() };
		Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y, width, height);
	}

	void RenderTextureComponent::SetTexture(const std::string& filename)
	{
		m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
	}
}
