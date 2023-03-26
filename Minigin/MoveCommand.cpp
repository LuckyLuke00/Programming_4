#include "MoveCommand.h"
#include "GameObject.h"

namespace dae
{
	MoveCommand::MoveCommand(GameObject* gameObject, const glm::vec3& direction, float moveSpeed) :
		Command{ gameObject },
		m_MoveSpeed{ moveSpeed },
		m_Direction{ direction },
		m_pTransformComponent{ gameObject->GetComponent<TransformComponent>() }
	{}

	void MoveCommand::Execute()
	{
	}
	
	void MoveCommand::Undo()
	{
	}
}