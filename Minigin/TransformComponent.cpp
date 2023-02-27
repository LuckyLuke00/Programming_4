#include "TransformComponent.h"

namespace dae
{
	TransformComponent::TransformComponent(const GameObject* pOwner, float x, float y, float z)
		: Component(pOwner)
	{
		m_Transform.SetPosition(x, y, z);
	}

	void TransformComponent::Update()
	{
	}

	void TransformComponent::SetPosition(float x, float y, float z)
	{
		m_Position.x = x;
		m_Position.y = y;
		m_Position.z = z;
	}
}