#include "LoadNextLevelCommand.h"
#include "GameManager.h"

namespace dae
{
	void LoadNextLevelCommand::Execute()
	{
		GameManager::GetInstance().LoadNextLevel();
	}

	void LoadNextLevelCommand::Undo()
	{
		GameManager::GetInstance().LoadPreviousLevel();
	}
}
