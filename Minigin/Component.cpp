#include "Component.h"
#include "GameObject.h"

namespace dae
{
	Component::Component(GameObject* pOwner) :
		m_pOwner{ pOwner }
	{}

	void Component::Update()
	{
		if (!m_pOwner->IsActive()) return;
	}

	void Component::FixedUpdate()
	{
		if (!m_pOwner->IsActive()) return;
	}

	void Component::LateUpdate()
	{
		if (!m_pOwner->IsActive()) return;
	}
}
