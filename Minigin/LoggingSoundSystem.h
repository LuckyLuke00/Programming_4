#pragma once
#include "ServiceLocator.h"
#include "SoundSystem.h"
#include <iostream>

namespace dae
{
	class LoggingSoundSystem final : public SoundSystem
	{
	public:
		explicit LoggingSoundSystem(std::unique_ptr<SoundSystem>&& pSoundSystem) : m_pSoundSystem(std::move(pSoundSystem)) {}
		~LoggingSoundSystem() override = default;

		void LoadMusic(const unsigned short soundId, const std::string& filePath) override
		{
			m_pSoundSystem->LoadMusic(soundId, filePath);
			std::cout << "LoadMusic: " << soundId << " with path: " << filePath << '\n';
		}

		void LoadSound(const unsigned short soundId, const std::string& filePath) override
		{
			m_pSoundSystem->LoadSound(soundId, filePath);
			std::cout << "LoadSound: " << soundId << " with path: " << filePath << '\n';
		}

		void PlaySound(const unsigned short soundId, const float volume) override
		{
			m_pSoundSystem->PlaySound(soundId, volume);
			std::cout << "PlaySound: " << soundId << " with volume: " << volume << '\n';
		}

		void PlayMusic(const unsigned short soundId, const float volume) override
		{
			m_pSoundSystem->PlayMusic(soundId, volume);
			std::cout << "PlayMusic: " << soundId << " with volume: " << volume << '\n';
		}

		void StopSound(const unsigned short soundId) override
		{
			m_pSoundSystem->StopSound(soundId);
			std::cout << "StopSound: " << soundId << '\n';
		}

		void StopMusic() override
		{
			m_pSoundSystem->StopMusic();
			std::cout << "StopMusic\n";
		}

	private:
		std::unique_ptr<SoundSystem> m_pSoundSystem;
	};
}
