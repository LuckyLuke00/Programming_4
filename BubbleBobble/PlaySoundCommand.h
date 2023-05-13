#pragma once
#include "Command.h"

namespace dae
{
	class PlaySoundCommand final : public Command
	{
	public:
		explicit PlaySoundCommand(const unsigned short soundId, const float volume);
		~PlaySoundCommand() override = default;

		PlaySoundCommand(const PlaySoundCommand& other) = delete;
		PlaySoundCommand(PlaySoundCommand&& other) noexcept = delete;
		PlaySoundCommand& operator=(const PlaySoundCommand& other) = delete;
		PlaySoundCommand& operator=(PlaySoundCommand&& other) noexcept = delete;
	private:
		const float m_Volume{ 1.f };
		const unsigned short m_SoundId{ 0 };

		void Execute() override;
	};
}
