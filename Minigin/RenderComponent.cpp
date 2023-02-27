#include "GameObject.h"
#include "RenderComponent.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "TransformComponent.h"

namespace dae
{
	RenderComponent::RenderComponent(const GameObject* pOwner)
		: Component(pOwner)
	{
	}

	void RenderComponent::Update()
	{
	}

	void RenderComponent::Render() const
	{
		if (m_Texture)
		{
			const auto& pos{ m_pOwner->GetComponent<TransformComponent>()->GetPosition() };
			Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
		}
	}

	void RenderComponent::SetTexture(const std::string& filename)
	{
		m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
	}
}