#include "PickupComponent.h"
#include "ColliderComponent.h"
#include "GameObject.h"
#include "RenderTextureComponent.h"
#include "GameManager.h"
#include <SoundSystem.h>
#include "SoundIds.h"

namespace dae
{
	Subject<PickupType, int> PickupComponent::m_OnPickup{};

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

	void PickupComponent::SetTexture(const std::string& filename)
	{
		m_pRenderTextureComponent->SetTexture(filename);
		m_pColliderComponent->SetDimensions(m_pRenderTextureComponent->GetTextureSize());
	}

	void PickupComponent::OnTrigger(const GameObject* other)
	{
		if (m_IsPickedUp || !other || other->GetTag() != "Player") return;

		// Get the player component
		if (const auto player{ other->GetComponent<PlayerComponent>() })
		{
			m_IsPickedUp = true;
			m_OnPickup.Notify(m_Type, player->GetPlayerId());
		}
		else return;

		GetOwner()->MarkForDelete();
		ServiceLocator<SoundSystem>::GetService().PlaySound(static_cast<unsigned short>(SoundIds::Pickup), .5f);
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
