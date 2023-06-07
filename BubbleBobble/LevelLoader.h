#pragma once
#include "Level.h"
#include <string>

namespace dae
{
	class LevelLoader
	{
	public:
		virtual ~LevelLoader() = default;

		LevelLoader(const LevelLoader& other) = delete;
		LevelLoader(LevelLoader&& other) noexcept = delete;
		LevelLoader& operator=(const LevelLoader& other) = delete;
		LevelLoader& operator=(LevelLoader&& other) noexcept = delete;

		static bool LoadLevel(Level& level);
	private:
		LevelLoader() = default;

		static bool ReadLevelFile(std::ifstream& file, Level& level);
	};
}
