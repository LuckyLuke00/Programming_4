#include "Component.h"

namespace dae
{
	Component::Component(const GameObject* pOwner)
		: m_pOwner{ pOwner }
	{
	}
}
