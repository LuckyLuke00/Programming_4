#include "GameObject.h"
#include "RenderComponent.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "TransformComponent.h"
#include <stdexcept>

namespace dae
{
	RenderComponent::RenderComponent(const GameObject* pOwner)
		: Component{ pOwner }
	{
		m_pTransformComponent = GetOwner()->GetComponent<TransformComponent>();
	}

	void RenderComponent::Render() const
	{
		if (!m_Texture) return;

		if (!m_pTransformComponent)
		{
			throw std::runtime_error(std::string("RenderComponent::Render() > GameObject does not have a TransformComponent!"));
		}

		const auto& pos{ m_pTransformComponent->GetPosition() };
		Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
	}

	void RenderComponent::SetTexture(const std::string& filename)
	{
		m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
	}
}
