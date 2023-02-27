#include "GameObject.h"
#include "RenderComponent.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "TransformComponent.h"
#include <stdexcept>

namespace dae
{
	RenderComponent::RenderComponent(const GameObject* pOwner)
		: Component(pOwner)
	{
	}

	void RenderComponent::Update()
	{
		// Nothing to do here
	}

	void RenderComponent::Render() const
	{
		if (!m_Texture) return;

		if (!GetOwner()->HasComponent<TransformComponent>())
		{
			throw std::runtime_error(std::string("RenderComponent::Render() > GameObject does not have a TransformComponent!"));
		}

		const auto& pos{ GetOwner()->GetComponent<TransformComponent>()->GetPosition() };
		Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
	}

	void RenderComponent::SetTexture(const std::string& filename)
	{
		m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
	}
}