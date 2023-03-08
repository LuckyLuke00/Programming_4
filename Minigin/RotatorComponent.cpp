#include "RotatorComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "Time.h"

dae::RotatorComponent::RotatorComponent(GameObject* pOwner)
	: Component{ pOwner }
{
	m_pTransformComponent = GetOwner()->GetComponent<TransformComponent>();
}

void dae::RotatorComponent::Update()
{
	if (!m_pTransformComponent) return;

	// Make sure the rotation is always between 0 and 360 degrees
	m_Rotation = glm::mod(m_Rotation + m_OrbitSpeed * Time::GetDeltaSeconds(), 360.f);

	m_pTransformComponent->SetPosition(m_OrbitCenter.x + m_OrbitRadius * cos(glm::radians(m_Rotation)), m_OrbitCenter.y + m_OrbitRadius * sin(glm::radians(m_Rotation)), m_OrbitCenter.z);
}
