#include "SDLSoundSystem.h"
#include <condition_variable>
#include <iostream>
#include <queue>
#include <SDL.h>
#include <SDL_mixer.h>
#include <unordered_map>

namespace dae
{
	class SDLSoundSystem::SDLSoundSystemImpl final
	{
	public:
		explicit SDLSoundSystemImpl()
		{
			if (SDL_Init(SDL_INIT_AUDIO) != 0)
			{
				throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
			}

			if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG | MIX_INIT_FLAC) < 0)
			{
				throw std::runtime_error(std::string("Mix_Init Error: ") + SDL_GetError());
			}

			if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096) != 0)
			{
				throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
			}

			m_SoundThread = std::jthread{ &SDLSoundSystemImpl::SoundThread, this };
		}

		~SDLSoundSystemImpl()
		{
			m_IsQuit = true;
			m_SoundConditionVariable.notify_one();

			for (auto& sound : m_SoundMap)
			{
				if (sound.second != nullptr)
				{
					Mix_FreeChunk(sound.second);
					sound.second = nullptr;
				}
			}

			for (auto& music : m_MusicMap)
			{
				if (music.second != nullptr)
				{
					Mix_FreeMusic(music.second);
					music.second = nullptr;
				}
			}

			Mix_CloseAudio();
			Mix_Quit();
		}

		void LoadMusic(const unsigned short soundId, const std::string& filePath)
		{
			// Add music to the map
			std::lock_guard<std::mutex> lock{ m_SoundMutex };
			// Add music to the queue
			m_MusicMap[soundId] = Mix_LoadMUS(filePath.c_str());

			// If loading failed, log error
			if (m_MusicMap[soundId] == nullptr)
			{
				std::cout << "Failed to load music: " << Mix_GetError() << '\n';
			}
		}

		void LoadSound(const unsigned short soundId, const std::string& filePath)
		{
			// Add sound to the map
			std::lock_guard<std::mutex> lock{ m_SoundMutex };

			// Add sound to the queue
			m_SoundMap[soundId] = Mix_LoadWAV(filePath.c_str());

			// If loading failed, log error
			if (m_SoundMap[soundId] == nullptr)
			{
				std::cout << "Failed to load sound: " << Mix_GetError() << '\n';
			}
		}

		void PlayMusic(const unsigned short soundId, const float volume)
		{
			const auto& music{ m_MusicMap[soundId] };

			if (music == nullptr)
			{
				std::cout << "Failed to play music: " << Mix_GetError() << '\n';
				return;
			}

			// Set volume
			Mix_VolumeMusic(static_cast<int>(MIX_MAX_VOLUME * std::clamp(volume, .0f, 1.f)));

			// Play music
			if (Mix_PlayMusic(music, -1) == -1)
			{
				std::cout << "Failed to play music: " << Mix_GetError() << '\n';
			}
		}

		void PlaySound(const unsigned short soundId, const float volume)
		{
			const auto& sound{ m_SoundMap[soundId] };
			if (sound == nullptr)
			{
				std::cout << "Failed to play sound: " << Mix_GetError() << '\n';
				return;
			}
			// Set volume
			Mix_VolumeChunk(sound, static_cast<int>(MIX_MAX_VOLUME * std::clamp(volume, .0f, 1.f)));
			// Play sound
			if (Mix_PlayChannel(-1, sound, 0) == -1)
			{
				std::cout << "Failed to play sound: " << Mix_GetError() << '\n';
			}
		}

		void StopMusic() const
		{
			Mix_HaltMusic();
		}

		void StopSound(const unsigned short soundId)
		{
			const auto& sound{ m_SoundMap[soundId] };
			if (sound == nullptr)
			{
				std::cout << "Failed to stop sound: " << Mix_GetError() << '\n';
				return;
			}
			Mix_HaltChannel(soundId);
		}

		// Sound thread stuff
		void SoundThread()
		{
			while (!m_IsQuit)
			{
				std::unique_lock<std::mutex> lock{ m_SoundMutex };
				m_SoundConditionVariable.wait(lock, [this] { return !m_SoundQueue.empty() || m_IsQuit; });
				if (m_IsQuit) return;

				while (!m_SoundQueue.empty())
				{
					const auto& [soundEvent, soundId, volume] { m_SoundQueue.front() };

					switch (soundEvent)
					{
					case SoundEvent::PlayMusic:
						PlayMusic(soundId, volume);
						break;

					case SoundEvent::PlaySound:
						PlaySound(soundId, volume);
						break;

					case SoundEvent::StopMusic:
						StopMusic();
						break;

					case SoundEvent::StopSound:
						StopSound(soundId);
						break;
					}

					m_SoundQueue.pop();
				}
			}
		}

	private:
		enum class SoundEvent : unsigned char
		{
			PlayMusic,
			PlaySound,
			StopMusic,
			StopSound,
		};

		std::atomic_bool m_IsQuit{ false };
		std::condition_variable m_SoundConditionVariable;
		std::jthread m_SoundThread;
		std::mutex m_SoundMutex;
		std::queue<std::tuple<SoundEvent, const unsigned short, float>> m_SoundQueue{};
		std::unordered_map<unsigned short, Mix_Chunk*> m_SoundMap{};
		std::unordered_map<unsigned short, Mix_Music*> m_MusicMap{};
	};

	SDLSoundSystem::SDLSoundSystem() :
		m_pImpl{ new SDLSoundSystemImpl{} }
	{}

	SDLSoundSystem::~SDLSoundSystem()
	{
		delete m_pImpl;
		m_pImpl = nullptr;
	}

	void SDLSoundSystem::PlaySound(const unsigned short soundId, const float volume)
	{
		m_pImpl->PlaySound(soundId, volume);
	}

	void SDLSoundSystem::PlayMusic(const unsigned short soundId, const float volume)
	{
		m_pImpl->PlayMusic(soundId, volume);
	}

	void SDLSoundSystem::StopSound(const unsigned short soundId)
	{
		m_pImpl->StopSound(soundId);
	}

	void SDLSoundSystem::StopMusic()
	{
		m_pImpl->StopMusic();
	}

	void SDLSoundSystem::LoadSound(const unsigned short soundId, const std::string& filePath)
	{
		m_pImpl->LoadSound(soundId, filePath);
	}

	void SDLSoundSystem::LoadMusic(const unsigned short soundId, const std::string& filePath)
	{
		m_pImpl->LoadMusic(soundId, filePath);
	}
}
