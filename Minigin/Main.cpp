#include <steam_api.h>
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
#include "HealthComponent.h"
#include "NumberDisplay.h"

#define DEMO_SCENE
#define FPS_COUNTER
#define COMMANDS
#define EVENTS

void load()
{
#ifdef DEMO_SCENE
	auto& demoScene{ dae::SceneManager::GetInstance().CreateScene("Demo Scene") };

	// Add background
	auto demoBackground{ std::make_unique<dae::GameObject>() };
	demoBackground->AddComponent<dae::TransformComponent>();
	demoBackground->AddComponent<dae::RenderTextureComponent>()->SetTexture("Images/background.tga");
	demoScene.Add(std::move(demoBackground));

	// Add logo
	auto demoLogo{ std::make_unique<dae::GameObject>() };
	demoLogo->AddComponent<dae::TransformComponent>()->SetPosition(216.f, 180.f);
	demoLogo->AddComponent<dae::RenderTextureComponent>()->SetTexture("Images/logo.tga");
	demoScene.Add(std::move(demoLogo));

	// Add text
	auto demoText{ std::make_unique<dae::GameObject>() };
	demoText->AddComponent<dae::TransformComponent>()->SetPosition(80.f, 20.f);
	demoText->AddComponent<dae::RenderTextureComponent>();

	auto* demoTextComponent{ demoText->AddComponent<dae::TextComponent>() };
	demoTextComponent->SetFont("Fonts/Lingua.otf", 36);
	demoTextComponent->SetText("Programming 4 Assignment");

	demoScene.Add(std::move(demoText));

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
	controller->AddCommand(std::move(moveCommand), dae::InputState::Pressed, dae::XboxController::XboxButton::DPadUp);

	// Down
	moveCommand = std::make_unique<dae::MoveCommand>(eggplantTransform, glm::vec2{ .0f, 1.f }, eggplantSpeed);
	controller->AddCommand(std::move(moveCommand), dae::InputState::Pressed, dae::XboxController::XboxButton::DPadDown);

	// Left
	moveCommand = std::make_unique<dae::MoveCommand>(eggplantTransform, glm::vec2{ -1.f, .0f }, eggplantSpeed);
	controller->AddCommand(std::move(moveCommand), dae::InputState::Pressed, dae::XboxController::XboxButton::DPadLeft);

	// Right
	moveCommand = std::make_unique<dae::MoveCommand>(eggplantTransform, glm::vec2{ 1.f, .0f }, eggplantSpeed);
	controller->AddCommand(std::move(moveCommand), dae::InputState::Pressed, dae::XboxController::XboxButton::DPadRight);

#endif // COMMANDS

#ifdef EVENTS

#endif // EVENTS
	// Create Bubblun health component
	auto bubblunHealthComponent = bubblun->AddComponent<dae::HealthComponent>();

	// Create Bubblun health display game object
	auto bubblunHealthDisplay = std::make_unique<dae::GameObject>();
	bubblunHealthDisplay->AddComponent<dae::TransformComponent>()->SetPosition(5.f, 250.f);
	bubblunHealthDisplay->AddComponent<dae::RenderTextureComponent>();

	// Create Bubblun health display text component
	auto* bubblunHealthDisplayText = bubblunHealthDisplay->AddComponent<dae::TextComponent>();
	bubblunHealthDisplayText->SetFont("Fonts/Lingua.otf", 18);
	bubblunHealthDisplayText->SetColor({ 255, 255, 0, 255 });

	// Create Bubblun number display component
	auto bubblunNumberDisplay = bubblunHealthDisplay->AddComponent<dae::NumberDisplay<unsigned int>>();
	bubblunNumberDisplay->SetText("Lives: ");
	bubblunNumberDisplay->SetValue(bubblunHealthComponent->GetLives());

	// Add observer to Bubblun health component
	bubblunHealthComponent->AddObserver(bubblunNumberDisplay->GetObserver());

	// Add Bubblun health display game object to demo scene
	demoScene.Add(std::move(bubblunHealthDisplay));

	// Create eggplant health component
	auto eggplantHealthComponent = eggplant->AddComponent<dae::HealthComponent>();

	// Create eggplant health display game object
	auto eggplantHealthDisplay = std::make_unique<dae::GameObject>();
	eggplantHealthDisplay->AddComponent<dae::TransformComponent>()->SetPosition(5.f, 350.f);
	eggplantHealthDisplay->AddComponent<dae::RenderTextureComponent>();

	// Create eggplant health display text component
	auto* eggplantHealthDisplayText = eggplantHealthDisplay->AddComponent<dae::TextComponent>();
	eggplantHealthDisplayText->SetFont("Fonts/Lingua.otf", 18);
	eggplantHealthDisplayText->SetColor({ 0, 255, 0, 255 });

	// Create eggplant number display component
	auto eggplantNumberDisplay = eggplantHealthDisplay->AddComponent<dae::NumberDisplay<unsigned int>>();
	eggplantNumberDisplay->SetText("Lives: ");
	eggplantNumberDisplay->SetValue(eggplantHealthComponent->GetLives());

	// Add observer to eggplant health component
	eggplantHealthComponent->AddObserver(eggplantNumberDisplay->GetObserver());

	// Add eggplant health display game object to demo scene
	demoScene.Add(std::move(eggplantHealthDisplay));

#pragma endregion
}

int main(int, char* []) {
	if (!SteamAPI_Init())
	{
		std::cerr << "Fatal Error - Steam must be running to play this game (SteamAPI_Init() failed).\n";
		return 1;
	}
	else
	{
		std::cout << "Successfully initialized steam.\n";
	}

	dae::Minigin engine("../Assets/");
	engine.Run(load);

	SteamAPI_Shutdown();
	return 0;
}
