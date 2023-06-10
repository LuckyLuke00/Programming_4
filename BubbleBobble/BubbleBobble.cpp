#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "FPSComponent.h"
#include "GameManager.h"
#include "GameObject.h"
#include "InputManager.h"
#include "LoadNextLevelCommand.h"
#include "LoggingSoundSystem.h"
#include "Minigin.h"
#include "PlaySoundCommand.h"
#include "RenderTextureComponent.h"
#include "Scene.h"
#include "SDLSoundSystem.h"
#include "TextComponent.h"

#define GAME_SCENE
#define LEVEL
#define PLAYER
#define FPS_COUNTER

void load()
{
#ifdef GAME_SCENE
	auto& gameScene{ dae::SceneManager::GetInstance().CreateScene("Game Scene") };

	const unsigned short soundId{ 0 };
	dae::ServiceLocator<dae::SoundSystem>::RegisterService(std::make_unique<dae::LoggingSoundSystem>(std::make_unique<dae::SDLSoundSystem>()));
	dae::ServiceLocator<dae::SoundSystem>::GetService().LoadSound(soundId, "../Assets/Sounds/test.wav");

	auto playSoundCommand{ std::make_unique<dae::PlaySoundCommand>(soundId, 1.f) };
	dae::InputManager::GetInstance().GetKeyboard().AddCommand(std::move(playSoundCommand), dae::InputState::Pressed, SDL_SCANCODE_E);

	// Green text
	std::cout << "\033[32m" << "Press E to play sound" << "\033[0m" << '\n';

#endif // GAME_SCENE

#ifdef LEVEL

	// Level 1
	auto level{ std::make_unique<dae::Level>(gameScene) };
	level->SetLevelName("Level 1");
	level->SetLevelFilePath("../Assets/Levels/level1.txt");
	dae::GameManager::GetInstance().AddLevel(std::move(level));

	// Level 2
	level = std::make_unique<dae::Level>(gameScene);
	level->SetLevelName("Level 2");
	level->SetLevelFilePath("../Assets/Levels/level2.txt");
	dae::GameManager::GetInstance().AddLevel(std::move(level));

	// Level 3
	level = std::make_unique<dae::Level>(gameScene);
	level->SetLevelName("Level 3");
	level->SetLevelFilePath("../Assets/Levels/level3.txt");
	dae::GameManager::GetInstance().AddLevel(std::move(level));

	// Load the first level
	dae::GameManager::GetInstance().LoadNextLevel();
	dae::InputManager::GetInstance().GetKeyboard().AddCommand(std::make_unique<dae::LoadNextLevelCommand>(), dae::InputState::Pressed, SDL_SCANCODE_F1);

#endif // LEVEL

#ifdef PLAYER

	// Player Animations
	dae::SpriteAnimation fall;
	fall.rows = 1;
	fall.cols = 2;
	fall.fps = 12;
	fall.frames = 2;

	dae::SpriteAnimation idle;
	idle.rows = 1;
	idle.cols = 5;
	idle.fps = 0;
	idle.frames = 1;

	dae::SpriteAnimation jump;
	jump.rows = 1;
	jump.cols = 2;
	jump.fps = 12;
	jump.frames = 2;

	dae::SpriteAnimation walk;
	walk.rows = 1;
	walk.cols = 5;
	walk.fps = 12;
	walk.frames = 5;

	// Player One
	auto playerOne{ std::make_shared<dae::GameObject>() };
	auto PlayerOneComponent{ playerOne->AddComponent<dae::PlayerComponent>() };

	// Player One: Animation Textures
	fall.SetTexture("Sprites/Player/Bub/bub_fall.png");
	idle.SetTexture("Sprites/Player/Bub/bub_walk.png");
	jump.SetTexture("Sprites/Player/Bub/bub_jump.png");
	walk.SetTexture("Sprites/Player/Bub/bub_walk.png");

	// Player One: Add Animations
	PlayerOneComponent->AddAnimation("Fall", fall);
	PlayerOneComponent->AddAnimation("Idle", idle);
	PlayerOneComponent->AddAnimation("Jump", jump);
	PlayerOneComponent->AddAnimation("Walk", walk);

	gameScene.Add(playerOne);
	dae::GameManager::GetInstance().AddPlayer(PlayerOneComponent);

	// Player Two
	auto playerTwo{ std::make_shared<dae::GameObject>() };
	auto playerTwoComponent{ playerTwo->AddComponent<dae::PlayerComponent>() };

	// Player Two: Animation Textures
	fall.SetTexture("Sprites/Player/Bob/bob_fall.png");
	idle.SetTexture("Sprites/Player/Bob/bob_walk.png");
	jump.SetTexture("Sprites/Player/Bob/bob_jump.png");
	walk.SetTexture("Sprites/Player/Bob/bob_walk.png");

	// Player Two: Add Animations
	playerTwoComponent->AddAnimation("Fall", fall);
	playerTwoComponent->AddAnimation("Idle", idle);
	playerTwoComponent->AddAnimation("Jump", jump);
	playerTwoComponent->AddAnimation("Walk", walk);

	gameScene.Add(playerTwo);
	dae::GameManager::GetInstance().AddPlayer(playerTwoComponent);

#endif // PLAYER

#ifdef FPS_COUNTER

	// Add FPS
	auto fps{ std::make_unique<dae::GameObject>() };
	fps->AddComponent<dae::TransformComponent>()->SetPosition(5.f, 5.f);
	fps->AddComponent<dae::RenderTextureComponent>();

	auto* fpsTextComponent{ fps->AddComponent<dae::TextComponent>() };
	fpsTextComponent->SetFont("Fonts/Lingua.otf", 18);
	fpsTextComponent->SetColor({ 0, 255, 0, 255 });

	fps->AddComponent<dae::FPSComponent>();

	gameScene.Add(std::move(fps));

#endif // FPS_COUNTER
}

int main(int, char* []) {
	dae::Minigin engine("../Assets/");
	engine.Run(load);

	return 0;
}
