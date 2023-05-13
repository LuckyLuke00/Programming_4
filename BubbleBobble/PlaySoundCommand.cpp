#include "PlaySoundCommand.h"
#include "SoundSystem.h"
#include "ServiceLocator.h"

namespace dae
{
	PlaySoundCommand::PlaySoundCommand(const unsigned short soundId, const float volume) :
		m_Volume{ volume },
		m_SoundId{ soundId }
	{}

	void PlaySoundCommand::Execute()
	{
		ServiceLocator<SoundSystem>::GetService().PlaySound(m_SoundId, m_Volume);
	}
}
