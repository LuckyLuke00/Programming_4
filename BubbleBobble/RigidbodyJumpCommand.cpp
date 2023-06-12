#include "RigidbodyJumpCommand.h"
#include "RigidbodyComponent.h"
#include "SoundSystem.h"
#include "SoundIds.h"

namespace dae
{
	RigidbodyJumpCommand::RigidbodyJumpCommand(RigidbodyComponent* rigidBody, const float& jumpForce) :
		m_JumpForce{ jumpForce },
		m_pRigidbodyComponent{ rigidBody }
	{}

	void RigidbodyJumpCommand::Execute()
	{
		if (!m_pRigidbodyComponent) return;
		if (!m_pRigidbodyComponent->IsGrounded()) return;

		m_pRigidbodyComponent->SetVelocity(glm::vec2{ m_pRigidbodyComponent->GetVelocity().x, -m_JumpForce });
		ServiceLocator<SoundSystem>::GetService().PlaySound(static_cast<unsigned short>(SoundIds::Jump), .5f);
	}
}
