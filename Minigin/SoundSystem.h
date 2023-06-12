#pragma once
#include "ServiceLocator.h"
#include <string>

namespace dae
{
	class SoundSystem
	{
	public:
		explicit SoundSystem() = default;
		virtual ~SoundSystem() = default;

		virtual void LoadMusic(const unsigned short soundId, const std::string& filePath) = 0;
		virtual void LoadSound(const unsigned short soundId, const std::string& filePath) = 0;

		virtual void PlayMusic(const unsigned short soundId, const float volume) = 0;
		virtual void PlaySound(const unsigned short soundId, const float volume) = 0;

		virtual void StopMusic() = 0;
		virtual void StopSound(const unsigned short soundId) = 0;

		virtual void Mute() = 0;
		virtual void Unmute() = 0;
	};

	template<class T>
	class NullService;

	template<>
	class NullService<SoundSystem> final : public SoundSystem
	{
	public:
		explicit NullService() = default;
		~NullService() override = default;

		// No '[[maybe_unused]]' you're welcome Alex <3
		void LoadMusic(const unsigned short, const std::string&) override { /*Do nothing*/ };
		void LoadSound(const unsigned short, const std::string&) override { /*Do nothing*/ };

		void PlayMusic(const unsigned short, const float) override { /*Do nothing*/ };
		void PlaySound(const unsigned short, const float) override { /*Do nothing*/ };

		void StopMusic() override { /*Do nothing*/ };
		void StopSound(const unsigned short) override { /*Do nothing*/ };

		void Mute() override { /*Do nothing*/ };
		void Unmute() override { /*Do nothing*/ };
	};
}
