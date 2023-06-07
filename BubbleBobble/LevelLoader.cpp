#include "LevelLoader.h"
#include <fstream>
#include <iostream>
#include <sstream>

namespace dae
{
	bool LevelLoader::LoadLevel(Level& level)
	{
		// Check if the levelPath is valid and if the file exists
		if (level.GetLevelFilePath().empty())
		{
			std::cerr << "LevelLoader::LoadLevel() - levelPath is empty\n";
			return false;
		}

		// Check if the file exists
		std::ifstream file{ level.GetLevelFilePath() };
		if (!file.is_open())
		{
			std::cerr << "LevelLoader::LoadLevel() - file could not be opened\n";
			return false;
		}

		if (!ReadLevelFile(file, level))
		{
			std::cerr << "LevelLoader::LoadLevel() - file could not be read\n";
			return false;
		}

		return true;
	}

	bool LevelLoader::ReadLevelFile(std::ifstream& file, Level& level)
	{
		// Container that stores the paths to the textures and the index it belongs to
		std::vector<std::pair<int, std::string>> tilePaths{};

		// Container that stores the indices and positions of the tiles
		std::vector<std::pair<int, std::pair<int, int>>> tileIndices{};

		// Go over every line in the file
		std::string line;
		while (std::getline(file, line))
		{
			// Check if the line is a comment
			if (line[0] == '#') continue;

			// If the current line is empty, skip it
			if (line.empty()) continue;

			// Indices and positions are written like this:
			// <index, (x, y)> <index, (x, y)> <index, (x, y)> ...
			// <1, (0, 0)> <2, (50, 50)>
			// Paths to the textures are written linked to the index like this:
			// index path
			// 1 Sprites/Tile1.png

			// Check if the line is a path to a texture
			if (line[0] != '<')
			{
				// Split the line into the index and the path
				std::istringstream iss{ line };
				int index{};
				std::string path{};
				iss >> index >> path;
				// Add the index and path to the tilePaths container
				tilePaths.emplace_back(index, path);
			}
			else
			{
				// Split the line into the indices and positions
				std::istringstream iss{ line };
				std::vector<std::pair<int, std::pair<int, int>>> indices{};
				// split every space between after the '>' and before the '<'
				std::string token;
				while (std::getline(iss, token, '>'))
				{
					// Remove the space at the beginning of the token if there is one
					if (token[0] == ' ') token.erase(0, 1);
					token.erase(0, 1);

					// Split the token into the index and the position
					std::istringstream ss{ token };
					int index{};
					int x{};
					int y{};
					char c{};
					ss >> index >> c >> c >> x >> c >> y;

					// Add the index and position to the indices container
					tileIndices.emplace_back(index, std::make_pair(x, y));
				}
			}
		}

		// Add the tiles to the level, get the index and position from the tileIndices container, and get the texturePath from the tilePaths container
		// To get the texturePath, we need to find the index in the tilePaths container that matches the index in the tileIndices container
		for (const auto& [iindex, position] : tileIndices)
		{
			// Get the index and position from the tileIndices container
			const int x{ position.first };
			const int y{ position.second };

			// Get the texturePath from the tilePaths container
			bool smallTile{ false };
			std::string texturePath{};
			for (const auto& [tindex, path] : tilePaths)
			{
				if (tindex == iindex)
				{
					texturePath = path;
					// If the index is not one, it is a small tile
					if (tindex != 1) smallTile = true;
					break;
				}
			}
			level.AddLevelTile({ x, y }, texturePath, smallTile);
		}

		level.ScaleToWindowSize();

		return true;
	}
}
