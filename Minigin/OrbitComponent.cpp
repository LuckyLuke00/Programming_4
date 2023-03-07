#include "OrbitComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "Time.h"

dae::OrbitComponent::OrbitComponent(GameObject* pOwner)
	: Component{ pOwner }
{
	m_pTransformComponent = GetOwner()->GetComponent<TransformComponent>();
}

void dae::OrbitComponent::Update()
{
	if (!m_pTransformComponent) return;

	m_Rotation += m_OrbitSpeed * Time::GetDeltaSeconds();
	m_pTransformComponent->SetPosition(m_OrbitCenter.x + m_OrbitRadius * cos(glm::radians(m_Rotation)), m_OrbitCenter.y + m_OrbitRadius * sin(glm::radians(m_Rotation)), m_OrbitCenter.z);
}
