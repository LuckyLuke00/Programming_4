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
		Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
	}

	void RenderTextureComponent::SetTexture(const std::string& filename)
	{
		m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
	}
}