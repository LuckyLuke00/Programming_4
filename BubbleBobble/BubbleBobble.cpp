#include <iostream>

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
#include "TransformComponent.h"
#include "InputManager.h"
#include "MoveCommand.h"
#include "SceneManager.h"
#include "LevelLoader.h"
#include "Level.h"

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

	dae::Level level1{ demoScene };
	dae::LevelLoader::LoadLevel("../Assets/Levels/level1.txt", level1);

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

	// Add Bubblun
	auto bubblun{ std::make_shared<dae::GameObject>() };
	bubblun->AddComponent<dae::TransformComponent>()->SetPosition(300.f, 360.f);
	bubblun->AddComponent<dae::RenderTextureComponent>()->SetTexture("Images/bubblun.png");
	auto bubblunTransform{ bubblun->GetComponent<dae::TransformComponent>() };
	demoScene.Add(bubblun);

	// Add Eggplant
	auto eggplant{ std::make_shared<dae::GameObject>() };
	eggplant->AddComponent<dae::TransformComponent>()->SetPosition(324.f, 360.f);
	eggplant->AddComponent<dae::RenderTextureComponent>()->SetTexture("Images/eggplant.png");
	auto eggplantTransform{ eggplant->GetComponent<dae::TransformComponent>() };
	demoScene.Add(eggplant);

	constexpr float bubblunSpeed{ 50.f };
	constexpr float eggplantSpeed{ bubblunSpeed * 2.f };

	// Player 1: Keyboard
	// Up
	auto moveCommand{ std::make_unique<dae::MoveCommand>(bubblunTransform, glm::vec2{ .0f, -1.f }, bubblunSpeed) };
	dae::InputManager::GetInstance().GetKeyboard().AddCommand(std::move(moveCommand), dae::InputState::Down, SDL_SCANCODE_W);

	// Down
	moveCommand = std::make_unique<dae::MoveCommand>(bubblunTransform, glm::vec2{ .0f, 1.f }, bubblunSpeed);
	dae::InputManager::GetInstance().GetKeyboard().AddCommand(std::move(moveCommand), dae::InputState::Down, SDL_SCANCODE_S);

	// Left
	moveCommand = std::make_unique<dae::MoveCommand>(bubblunTransform, glm::vec2{ -1.f, .0f }, bubblunSpeed);
	dae::InputManager::GetInstance().GetKeyboard().AddCommand(std::move(moveCommand), dae::InputState::Down, SDL_SCANCODE_A);

	// Right
	moveCommand = std::make_unique<dae::MoveCommand>(bubblunTransform, glm::vec2{ 1.f, .0f }, bubblunSpeed);
	dae::InputManager::GetInstance().GetKeyboard().AddCommand(std::move(moveCommand), dae::InputState::Down, SDL_SCANCODE_D);

	// Player 2: Gamepad
	// Add a controller
	auto controller{ dae::InputManager::GetInstance().AddXboxController() };

	// Up
	moveCommand = std::make_unique<dae::MoveCommand>(eggplantTransform, glm::vec2{ .0f, -1.f }, eggplantSpeed);
	controller->AddCommand(std::move(moveCommand), dae::InputState::Down, dae::XboxController::XboxButton::DPadUp);

	// Down
	moveCommand = std::make_unique<dae::MoveCommand>(eggplantTransform, glm::vec2{ .0f, 1.f }, eggplantSpeed);
	controller->AddCommand(std::move(moveCommand), dae::InputState::Down, dae::XboxController::XboxButton::DPadDown);

	// Left
	moveCommand = std::make_unique<dae::MoveCommand>(eggplantTransform, glm::vec2{ -1.f, .0f }, eggplantSpeed);
	controller->AddCommand(std::move(moveCommand), dae::InputState::Down, dae::XboxController::XboxButton::DPadLeft);

	// Right
	moveCommand = std::make_unique<dae::MoveCommand>(eggplantTransform, glm::vec2{ 1.f, .0f }, eggplantSpeed);
	controller->AddCommand(std::move(moveCommand), dae::InputState::Down, dae::XboxController::XboxButton::DPadRight);

#endif // COMMANDS
}

int main(int, char* []) {
	dae::Minigin engine("../Assets/");
	engine.Run(load);

	return 0;
}
