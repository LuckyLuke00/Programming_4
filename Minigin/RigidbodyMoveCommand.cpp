#include "RigidbodyMoveCommand.h"
#include "RigidbodyComponent.h"
#include <iostream>

namespace dae
{
	RigidbodyMoveCommand::RigidbodyMoveCommand(RigidbodyComponent* rigidBody, const glm::vec2& direction, const float& speed) :
		m_Direction{ glm::normalize(direction) },
		m_Speed{ speed },
		m_pRigidbodyComponent{ rigidBody }
	{}

	void RigidbodyMoveCommand::Execute()
	{
		if (!m_pRigidbodyComponent) return;
		m_pRigidbodyComponent->AddForce(m_Direction * m_Speed);
	}
}
