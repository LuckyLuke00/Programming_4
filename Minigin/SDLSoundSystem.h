#pragma once
#include "SoundSystem.h"

namespace dae
{
	class SDLSoundSystem final : public SoundSystem
	{
	public:
		explicit SDLSoundSystem();
		~SDLSoundSystem() override;

		void LoadMusic(const unsigned short soundId, const std::string& filePath) override;
		void LoadSound(const unsigned short soundId, const std::string& filePath) override;

		void PlayMusic(const unsigned short soundId, const float volume) override;
		void PlaySound(const unsigned short soundId, const float volume) override;

		void StopMusic() override;
		void StopSound(const unsigned short soundId) override;

		void Mute() override;
		void Unmute() override;

	private:
		class SDLSoundSystemImpl;
		SDLSoundSystemImpl* m_pImpl;
	};
}
