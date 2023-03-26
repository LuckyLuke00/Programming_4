#include "TransformComponent.h"
#include "GameObject.h"

namespace dae
{
	TransformComponent::TransformComponent(GameObject* pOwner) :
		Component{ pOwner }
	{}

	const glm::vec3& TransformComponent::GetWorldPosition()
	{
		if (m_IsDirty)
		{
			UpdateTransform();
		}
		return m_WorldPosition;
	}

	void TransformComponent::SetPosition(float x, float y, float z)
	{
		m_LocalPosition.x = x;
		m_LocalPosition.y = y;
		m_LocalPosition.z = z;

		SetDirty();
	}

	void TransformComponent::UpdateTransform()
	{
		// If there is no parent, the world position is the local position
		if (!GetOwner()->GetParent())
		{
			m_WorldPosition = m_LocalPosition;
			return;
		}

		// Get the parent's transform component
		auto* pParentTransform{ GetOwner()->GetParent()->GetTransformComponent() };
		if (!pParentTransform) return;

		// Set the world position
		m_WorldPosition = m_LocalPosition + pParentTransform->GetWorldPosition();

		m_IsDirty = false;
	}

	void TransformComponent::SetDirty()
	{
		m_IsDirty = true;

		for (const auto* pChild : GetOwner()->GetChildren())
		{
			auto* pTransformComponent{ pChild->GetTransformComponent() };
			if (!pTransformComponent) continue;
			pTransformComponent->SetDirty();
		}
	}
}