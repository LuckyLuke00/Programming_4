#include "MoveCommand.h"
#include "GameObject.h"
#include "Time.h"

namespace dae
{
	MoveCommand::MoveCommand(GameObject* gameObject, const glm::vec3& direction, float moveSpeed) :
		Command{ gameObject },
		m_MoveSpeed{ moveSpeed },
		m_Direction{ glm::normalize(direction) },
		m_pTransformComponent{ gameObject->GetComponent<TransformComponent>() }
	{}

	void MoveCommand::Execute()
	{
		if (!m_pTransformComponent) return;

		m_LastPosition = m_pTransformComponent->GetLocalPosition();
		m_pTransformComponent->Translate(m_Direction * m_MoveSpeed * Time::GetDeltaSeconds());
	}

	void MoveCommand::Undo()
	{
		if (!m_pTransformComponent) return;

		m_pTransformComponent->SetPosition(m_LastPosition);
	}
}
