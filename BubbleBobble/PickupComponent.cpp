#include "PickupComponent.h"
#include "ColliderComponent.h"
#include "GameObject.h"
#include "RenderTextureComponent.h"
#include "GameManager.h"

namespace dae
{
	PickupComponent::PickupComponent(GameObject* pOwner) :
		Component{ pOwner },
		m_pTransformComponent{ pOwner->AddComponent<TransformComponent>() },
		m_pRenderTextureComponent{ pOwner->AddComponent<RenderTextureComponent>() },
		m_pColliderComponent{ pOwner->AddComponent<ColliderComponent>() }
	{
		pOwner->SetTag("Pickup");
		m_pColliderComponent->SetIsTrigger(true);
		m_pColliderComponent->SetTriggerCallback(std::bind_front(&PickupComponent::OnTrigger, this));

		ScaleToLevelSize();
	}

	int PickupComponent::PickUp() const
	{
		GetOwner()->MarkForDelete();
		return m_Points;
	}

	void PickupComponent::OnTrigger(const GameObject* other) const
	{
		if (!other || other->GetTag() != "Player") return;
		PickUp();
	}

	void PickupComponent::ScaleToLevelSize()
	{
		const auto& level{ GameManager::GetInstance().GetCurrentLevel() };
		if (!level) return;

		const float levelScale{ level->GetLevelScale() };

		// Subtract a quarter of the scale, so the player is centered
		const float scale{ levelScale - (levelScale / 4.f) };
		m_pTransformComponent->SetScale(scale); // Set the scale of the player based on the level scale
	}
}
