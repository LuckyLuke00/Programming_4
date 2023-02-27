#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "GameObject.h"
#include "RenderComponent.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "SceneManager.h"
#include "TextComponent.h"

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	auto background{ std::make_shared<dae::GameObject>() };
	background->AddComponent<dae::RenderComponent>()->SetTexture("background.tga");
	background->AddComponent<dae::TransformComponent>();
	scene.Add(background);

	auto logo{ std::make_shared<dae::GameObject>() };
	logo->AddComponent<dae::RenderComponent>()->SetTexture("logo.tga");
	logo->AddComponent<dae::TransformComponent>()->SetPosition(216.f, 180.f, .0f);
	scene.Add(logo);

	auto font{ std::make_shared<dae::GameObject>() };
	font->AddComponent<dae::RenderComponent>();
	font->AddComponent<dae::TransformComponent>()->SetPosition(80.f, 20.f, .0f);
	font->AddComponent<dae::TextComponent>()->SetFont("Lingua.otf", 36);
	font->GetComponent<dae::TextComponent>()->SetText("Programming 4 Assignment");
	scene.Add(font);
}

int main(int, char* []) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}
