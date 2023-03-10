#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "FPSComponent.h"
#include "GameObject.h"
#include "Minigin.h"
#include "RenderComponent.h"
#include "RotatorComponent.h"
#include "Scene.h"
#include "TextComponent.h"

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	// Add background
	auto background{ std::make_shared<dae::GameObject>() };
	background->AddComponent<dae::TransformComponent>();
	background->AddComponent<dae::RenderComponent>()->SetTexture("background.tga");
	scene.Add(background);

	// Add logo
	auto logo{ std::make_shared<dae::GameObject>() };
	logo->AddComponent<dae::TransformComponent>()->SetPosition(216.f, 180.f, .0f);
	logo->AddComponent<dae::RenderComponent>()->SetTexture("logo.tga");
	scene.Add(logo);

	// Add text
	auto font{ std::make_shared<dae::GameObject>() };
	font->AddComponent<dae::TransformComponent>()->SetPosition(80.f, 20.f, .0f);
	font->AddComponent<dae::RenderComponent>();
	font->AddComponent<dae::TextComponent>()->SetFont("Lingua.otf", 36);
	font->GetComponent<dae::TextComponent>()->SetText("Programming 4 Assignment");
	scene.Add(font);

	// Add FPS
	auto fps{ std::make_shared<dae::GameObject>() };
	fps->AddComponent<dae::TransformComponent>()->SetPosition(5.f, 5.f, .0f);
	fps->AddComponent<dae::RenderComponent>();
	fps->AddComponent<dae::TextComponent>()->SetFont("Lingua.otf", 18);
	fps->GetComponent<dae::TextComponent>()->SetColor({ 255, 255, 0, 255 });
	fps->AddComponent<dae::FPSComponent>();
	scene.Add(fps);

	// Add Bubblun
	auto bubblun{ std::make_shared<dae::GameObject>() };
	bubblun->AddComponent<dae::TransformComponent>()->SetPosition(312.f, 360.f, .0f);
	bubblun->AddComponent<dae::RenderComponent>()->SetTexture("Assets/Images/bubblun.png");
	scene.Add(bubblun);

	// Add orbit component to Bubblun
	bubblun->AddComponent<dae::RotatorComponent>()->SetRotationCenter({ 312.f, 360.f, .0f });
	bubblun->GetComponent<dae::RotatorComponent>()->SetRotationRadius(15.f);
	bubblun->GetComponent<dae::RotatorComponent>()->SetRotationSpeed(-100.f);

	// Add Eggplant
	auto eggplant{ std::make_shared<dae::GameObject>() };
	eggplant->AddComponent<dae::TransformComponent>()->SetPosition(312.f, 360.f, .0f);
	eggplant->AddComponent<dae::RenderComponent>()->SetTexture("Assets/Images/eggplant.png");
	scene.Add(eggplant);

	// Add orbit component to Eggplant
	eggplant->AddComponent<dae::RotatorComponent>()->SetRotationCenter({ .0f, .0f, .0f });
	eggplant->GetComponent<dae::RotatorComponent>()->SetRotationRadius(25.f);
	eggplant->GetComponent<dae::RotatorComponent>()->SetRotationSpeed(100.f);

	bubblun->AddChild(eggplant.get());
}

int main(int, char* []) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}
