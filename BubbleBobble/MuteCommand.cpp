#include "MuteCommand.h"
#include "SoundSystem.h"
#include "ServiceLocator.h"

namespace dae
{
	void MuteCommand::Execute()
	{
		m_IsMuted ? ServiceLocator<SoundSystem>::GetService().Unmute() : ServiceLocator<SoundSystem>::GetService().Mute();
		m_IsMuted = !m_IsMuted;
	}
}
