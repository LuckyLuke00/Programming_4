#include "RenderSpriteComponent.h"
#include "RenderSpriteComponent.h"
#include "GameObject.h"
#include "Timer.h"
#include "Renderer.h"

namespace dae
{
	RenderSpriteComponent::RenderSpriteComponent(GameObject* pOwner) :
		RenderComponent{ pOwner },
		m_pTransformComponent{ pOwner->GetComponent<TransformComponent>() }
	{
	}

	void RenderSpriteComponent::Render()
	{
		if (!IsEnabled() || !m_pCurrentAnimation || !m_pCurrentAnimation->m_Texture || !m_pTransformComponent) return;

		const auto pos{ m_pTransformComponent->GetWorldPosition() };

		m_pCurrentAnimation->totalTime += Timer::GetDeltaSeconds();

		const float srcWidth{ static_cast<float>(m_pCurrentAnimation->m_Texture->GetSize().x / m_pCurrentAnimation->cols) };
		const float srcHeight{ static_cast<float>(m_pCurrentAnimation->m_Texture->GetSize().y / m_pCurrentAnimation->rows) };

		const float dstWidth{ srcWidth * m_pTransformComponent->GetScale() };
		const float dstHeight{ srcHeight * m_pTransformComponent->GetScale() };

		// Calculate the current frame
		const int currentFrame{ static_cast<int>(m_pCurrentAnimation->totalTime * m_pCurrentAnimation->fps) % m_pCurrentAnimation->frames };

		// Reset the timer if the animation is done
		if (m_pCurrentAnimation->totalTime >= static_cast<float>(m_pCurrentAnimation->frames) / static_cast<float>(m_pCurrentAnimation->fps))
			m_pCurrentAnimation->totalTime = .0f;

		// Calculate the src position
		const float srcX{ (currentFrame % m_pCurrentAnimation->cols) * srcWidth };
		const float srcY{ (currentFrame / m_pCurrentAnimation->cols) * srcHeight };

		Renderer::GetInstance().RenderTexture(*m_pCurrentAnimation->m_Texture, pos.x, pos.y, m_FlipX ? -dstWidth : dstWidth, dstHeight, srcX, srcY, srcWidth, srcHeight);
	}

	void RenderSpriteComponent::AddAnimation(const std::string& name, const SpriteAnimation& animation)
	{
		m_Animations[name] = animation;

		// The first animation added is the default animation
		if (!m_pCurrentAnimation)
		{
			m_pCurrentAnimation = &m_Animations[name];
		}
	}

	void RenderSpriteComponent::SetAnimation(const std::string& name)
	{
		// Check if the animation exists
		if (!m_Animations.contains(name)) return;

		m_pCurrentAnimation->totalTime = .0f;
		m_pCurrentAnimation = &m_Animations[name];
	}
	glm::vec2 dae::RenderSpriteComponent::GetFrameSize() const
	{
		if (!m_pCurrentAnimation) return glm::vec2{};

		const float srcWidth{ static_cast<float>(m_pCurrentAnimation->m_Texture->GetSize().x / m_pCurrentAnimation->cols) };
		const float srcHeight{ static_cast<float>(m_pCurrentAnimation->m_Texture->GetSize().y / m_pCurrentAnimation->rows) };

		return glm::vec2{ srcWidth, srcHeight };
	}
}
