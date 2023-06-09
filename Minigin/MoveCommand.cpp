#include "MoveCommand.h"
#include "GameObject.h"
#include "Timer.h"

namespace dae
{
	MoveCommand::MoveCommand(TransformComponent* transform, const glm::vec2& direction, float moveSpeed, const std::function<void()>& executeFunction) :
		m_ExecuteFunction{ executeFunction },
		m_MoveSpeed{ moveSpeed },
		m_Direction{ glm::normalize(direction) },
		m_pTransformComponent{ transform }
	{}

	void MoveCommand::Execute()
	{
		if (!m_pTransformComponent) return;

		m_LastPosition = m_pTransformComponent->GetLocalPosition();
		m_pTransformComponent->Translate(m_Direction * m_MoveSpeed * Timer::GetDeltaSeconds());

		if (m_ExecuteFunction) m_ExecuteFunction();
	}

	void MoveCommand::Undo()
	{
		if (!m_pTransformComponent) return;

		m_pTransformComponent->SetPosition(m_LastPosition);
	}
}
