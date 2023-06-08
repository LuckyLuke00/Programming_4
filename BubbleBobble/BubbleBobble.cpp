#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "FPSComponent.h"
#include "GameObject.h"
#include "Minigin.h"
#include "RenderTextureComponent.h"
#include "Scene.h"
#include "TextComponent.h"
#include "InputManager.h"
#include "LevelLoader.h"
#include <LoggingSoundSystem.h>
#include <SDLSoundSystem.h>
#include "PlaySoundCommand.h"
#include "PlayerComponent.h"
#include "GameManager.h"
#include "LoadNextLevelCommand.h"

#define DEMO_SCENE
#define FPS_COUNTER
#define COMMANDS
#define EVENTS

void load()
{
#ifdef DEMO_SCENE
	auto& demoScene{ dae::SceneManager::GetInstance().CreateScene("Demo Scene") };

	//// Add background
	//auto demoBackground{ std::make_unique<dae::GameObject>() };
	//demoBackground->AddComponent<dae::TransformComponent>();
	//demoBackground->AddComponent<dae::RenderTextureComponent>()->SetTexture("Images/background.tga");
	//demoScene.Add(std::move(demoBackground));

	//// Add logo
	//auto demoLogo{ std::make_unique<dae::GameObject>() };
	//demoLogo->AddComponent<dae::TransformComponent>()->SetPosition(216.f, 180.f);
	//demoLogo->AddComponent<dae::RenderTextureComponent>()->SetTexture("Images/logo.tga");
	//demoScene.Add(std::move(demoLogo));

	//// Add text
	//auto demoText{ std::make_unique<dae::GameObject>() };
	//demoText->AddComponent<dae::TransformComponent>()->SetPosition(80.f, 20.f);
	//demoText->AddComponent<dae::RenderTextureComponent>();

	//auto* demoTextComponent{ demoText->AddComponent<dae::TextComponent>() };
	//demoTextComponent->SetFont("Fonts/Lingua.otf", 36);
	//demoTextComponent->SetText("Programming 4 Assignment");

	//demoScene.Add(std::move(demoText));

	// Create a uniqe pointer to a level
	auto level{ std::make_unique<dae::Level>(demoScene) };
	level->SetLevelName("Level 1");
	level->SetLevelFilePath("../Assets/Levels/level1.txt");
	dae::GameManager::GetInstance().AddLevel(std::move(level));

	level = std::make_unique<dae::Level>(demoScene);
	level->SetLevelName("Level 2");
	level->SetLevelFilePath("../Assets/Levels/level2.txt");

	dae::GameManager::GetInstance().AddLevel(std::move(level));

	level = std::make_unique<dae::Level>(demoScene);
	level->SetLevelName("Level 3");
	level->SetLevelFilePath("../Assets/Levels/level3.txt");

	dae::GameManager::GetInstance().AddLevel(std::move(level));
	dae::GameManager::GetInstance().LoadNextLevel();

	dae::InputManager::GetInstance().GetKeyboard().AddCommand(std::make_unique<dae::LoadNextLevelCommand>(), dae::InputState::Pressed, SDL_SCANCODE_F1);

	const unsigned short soundId{ 0 };
	dae::ServiceLocator<dae::SoundSystem>::RegisterService(std::make_unique<dae::LoggingSoundSystem>(std::make_unique<dae::SDLSoundSystem>()));
	dae::ServiceLocator<dae::SoundSystem>::GetService().LoadSound(soundId, "../Assets/Sounds/test.wav");

	auto playSoundCommand{ std::make_unique<dae::PlaySoundCommand>(soundId, 1.f) };
	dae::InputManager::GetInstance().GetKeyboard().AddCommand(std::move(playSoundCommand), dae::InputState::Pressed, SDL_SCANCODE_E);

	// Green text
	std::cout << "\033[32m" << "Press E to play sound" << "\033[0m" << '\n';

#endif // DEMO_SCENE

#ifdef FPS_COUNTER

	// Add FPS
	auto fps{ std::make_unique<dae::GameObject>() };
	fps->AddComponent<dae::TransformComponent>()->SetPosition(5.f, 5.f);
	fps->AddComponent<dae::RenderTextureComponent>();

	auto* fpsTextComponent{ fps->AddComponent<dae::TextComponent>() };
	fpsTextComponent->SetFont("Fonts/Lingua.otf", 18);
	fpsTextComponent->SetColor({ 0, 255, 0, 255 });

	fps->AddComponent<dae::FPSComponent>();

	demoScene.Add(std::move(fps));

#endif // FPS_COUNTER

#ifdef COMMANDS

	// Add Player 1
	auto playerOne{ std::make_shared<dae::GameObject>() };
	auto PlayerOneComponent{ playerOne->AddComponent<dae::PlayerComponent>() };
	PlayerOneComponent->SetPosition({ 300.f, 360.f });
	dae::SpriteAnimation walk;
	walk.rows = 1;
	walk.cols = 5;
	walk.fps = 12;
	walk.frames = 5;
	walk.SetTexture("Sprites/Player/Bubblun/bubblun_walk.png");
	PlayerOneComponent->AddAnimation("Walking", walk);

	//PlayerOneComponent->SetTexturePath("Sprites/Player/Bubblun/bubblun_walk.png");
	demoScene.Add(playerOne);

	//// Add Player 2
	//auto playerTwo{ std::make_shared<dae::GameObject>() };
	//auto playerTwoComponent{ playerTwo->AddComponent<dae::PlayerComponent>() };

	//playerTwoComponent->SetPosition({ 360.f, 360.f });
	//demoScene.Add(playerTwo);

#endif // COMMANDS
}

int main(int, char* []) {
	dae::Minigin engine("../Assets/");
	engine.Run(load);

	return 0;
}
