#include "PlayerComponent.h"
#include "CollisionEvent.h"
#include "MoveCommand.h"
#include "InputManager.h"
#include "TransformComponent.h"
#include "GameObject.h"
#include <memory>

namespace dae
{
	PlayerComponent::PlayerComponent(GameObject* pOwner) :
		Component{ pOwner }
	{
	}

	PlayerComponent::~PlayerComponent()
	{
	}

	void PlayerComponent::Update()
	{
	}
}
