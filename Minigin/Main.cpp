#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "FPSComponent.h"
#include "GameObject.h"
#include "InputManager.h"
#include "Minigin.h"
#include "MoveCommand.h"
#include "Renderer.h"
#include "RenderTextureComponent.h"
#include "RotatorComponent.h"
#include "Scene.h"
#include "TextComponent.h"
#include "TrashTheCache.h"

// Scenes
//#define TRASH_THE_CACHE_SCENE

#ifndef TRASH_THE_CACHE_SCENE
// Demo Scene
#define DEMO_SCENE
#define FPS_COUNTER
//#define SCENEGRAPH
#define COMMANDS
#endif // !TRASH_THE_CACHE_SCENE

void load()
{
#ifdef DEMO_SCENE

	auto& demoScene{ dae::SceneManager::GetInstance().CreateScene("Demo Scene") };

	// Add background
	auto background{ std::make_unique<dae::GameObject>() };
	background->AddComponent<dae::TransformComponent>();
	background->AddComponent<dae::RenderTextureComponent>()->SetTexture("background.tga");
	demoScene.Add(std::move(background));

	// Add logo
	auto logo{ std::make_unique<dae::GameObject>() };
	logo->AddComponent<dae::TransformComponent>()->SetPosition(216.f, 180.f);
	logo->AddComponent<dae::RenderTextureComponent>()->SetTexture("logo.tga");
	demoScene.Add(std::move(logo));

	// Add text
	auto font{ std::make_unique<dae::GameObject>() };
	font->AddComponent<dae::TransformComponent>()->SetPosition(80.f, 20.f);
	font->AddComponent<dae::RenderTextureComponent>();
	font->AddComponent<dae::TextComponent>()->SetFont("Lingua.otf", 36);
	font->GetComponent<dae::TextComponent>()->SetText("Programming 4 Assignment");
	demoScene.Add(std::move(font));

#endif // DEMO_SCENE

#ifdef FPS_COUNTER

	// Add FPS
	auto fps{ std::make_unique<dae::GameObject>() };
	fps->AddComponent<dae::TransformComponent>()->SetPosition(5.f, 5.f);
	fps->AddComponent<dae::RenderTextureComponent>();
	fps->AddComponent<dae::TextComponent>()->SetFont("Lingua.otf", 18);
	fps->GetComponent<dae::TextComponent>()->SetColor({ 255, 255, 0, 255 });
	fps->AddComponent<dae::FPSComponent>();
	demoScene.Add(std::move(fps));

#endif // DEMO_SCENE

#ifdef SCENEGRAPH

	// Add Bubblun
	auto bubblun{ std::make_shared<dae::GameObject>() };
	bubblun->AddComponent<dae::TransformComponent>()->SetPosition(312.f, 360.f);
	bubblun->AddComponent<dae::RenderTextureComponent>()->SetTexture("Assets/Images/bubblun.png");

	// Add orbit component to Bubblun
	bubblun->AddComponent<dae::RotatorComponent>()->SetRotationCenter({ 312.f, 360.f });
	bubblun->GetComponent<dae::RotatorComponent>()->SetRotationRadius(15.f);
	bubblun->GetComponent<dae::RotatorComponent>()->SetRotationSpeed(-100.f);

	demoScene.Add(bubblun);

	// Add Eggplant
	auto eggplant{ std::make_shared<dae::GameObject>() };
	eggplant->AddComponent<dae::TransformComponent>()->SetPosition(312.f, 360.f);
	eggplant->AddComponent<dae::RenderTextureComponent>()->SetTexture("Assets/Images/eggplant.png");
	demoScene.Add(eggplant);

	// Add orbit component to Eggplant
	eggplant->AddComponent<dae::RotatorComponent>()->SetRotationCenter({ .0f, .0f });
	eggplant->GetComponent<dae::RotatorComponent>()->SetRotationRadius(25.f);
	eggplant->GetComponent<dae::RotatorComponent>()->SetRotationSpeed(100.f);

	bubblun->AddChild(eggplant.get());

#endif // SCENEGRAPH

#ifdef TRASH_THE_CACHE_SCENE

	auto& scene{ dae::SceneManager::GetInstance().CreateScene("TrashTheCache") };

	// Add text
	auto font{ std::make_unique<dae::GameObject>() };
	font->AddComponent<dae::TransformComponent>()->SetPosition(80.f, 20.f);
	font->AddComponent<dae::RenderTextureComponent>();
	font->AddComponent<dae::TextComponent>()->SetFont("Lingua.otf", 36);
	font->GetComponent<dae::TextComponent>()->SetText("Programming 4 Assignment");
	scene.Add(std::move(font));

	auto trashTheCache{ std::make_unique<dae::GameObject>() };
	trashTheCache->AddComponent<dae::TrashTheCache>();
	scene.Add(std::move(trashTheCache));

	// Set the background color
	dae::Renderer::GetInstance().SetBackgroundColor(SDL_Color(62, 90, 111));

#endif // TRASH_THE_CACHE_SCENE

#ifdef COMMANDS

	// Add Bubblun
	auto bubblun{ std::make_shared<dae::GameObject>() };
	bubblun->AddComponent<dae::TransformComponent>()->SetPosition(300.f, 360.f);
	bubblun->AddComponent<dae::RenderTextureComponent>()->SetTexture("Assets/Images/bubblun.png");
	auto bubblunTransform{ bubblun->GetComponent<dae::TransformComponent>() };
	demoScene.Add(bubblun);

	// Add Eggplant
	auto eggplant{ std::make_shared<dae::GameObject>() };
	eggplant->AddComponent<dae::TransformComponent>()->SetPosition(324.f, 360.f);
	eggplant->AddComponent<dae::RenderTextureComponent>()->SetTexture("Assets/Images/eggplant.png");
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

#pragma endregion
}

int main(int, char* []) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}
