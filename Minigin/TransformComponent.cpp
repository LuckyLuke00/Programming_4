#include "TransformComponent.h"

namespace dae
{
	TransformComponent::TransformComponent(const GameObject* pOwner)
		: Component(pOwner)
	{
	}

	void TransformComponent::Update()
	{
		// Nothing to do here
	}

	void TransformComponent::SetPosition(float x, float y, float z)
	{
		m_Position.x = x;
		m_Position.y = y;
		m_Position.z = z;
	}
}