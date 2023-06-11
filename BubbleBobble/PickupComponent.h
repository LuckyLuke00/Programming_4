#pragma once
#include "Component.h"
#include "TransformComponent.h"
#include "RenderTextureComponent.h"
#include "Subject.h"

namespace dae
{
	class TransformComponent;
	class RenderTextureComponent;
	class ColliderComponent;

	enum class PickupType
	{
		Watermelon,
		Fries,
	};

	class PickupComponent final : public Component
	{
	public:
		explicit PickupComponent(GameObject* pOwner);
		~PickupComponent() override = default;

		PickupComponent(const PickupComponent& other) = delete;
		PickupComponent(PickupComponent&& other) noexcept = delete;
		PickupComponent& operator=(const PickupComponent& other) = delete;
		PickupComponent& operator=(PickupComponent&& other) noexcept = delete;

		void SetPickupType(PickupType type) { m_Type = type; }
		void SetPosition(const glm::vec2& pos) { m_pTransformComponent->SetPosition(pos); }
		void SetTexture(const std::string& filename) { m_pRenderTextureComponent->SetTexture(filename); }

		static Subject<PickupType, int> m_OnPickup;

	private:
		PickupType m_Type{ -1 };

		TransformComponent* m_pTransformComponent{ nullptr };
		RenderTextureComponent* m_pRenderTextureComponent{ nullptr };
		ColliderComponent* m_pColliderComponent{ nullptr };

		void OnTrigger(const GameObject* other);
		void ScaleToLevelSize();
	};
}
