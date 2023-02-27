#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "TextObject.h"
#include "Scene.h"
#include "RenderComponent.h"

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	auto background{ std::make_shared<dae::GameObject>() };
	background->AddComponent<dae::RenderComponent>()->SetTexture("background.tga");
	background->AddComponent<dae::TransformComponent>()->SetPosition(.0f, .0f, .0f);
	scene.Add(background);

	auto logo{ std::make_shared<dae::GameObject>() };
	logo->AddComponent<dae::RenderComponent>()->SetTexture("logo.tga");
	logo->AddComponent<dae::TransformComponent>()->SetPosition(216.f, 180.f, .0f);
	scene.Add(logo);

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	//auto to = std::make_shared<dae::TextObject>("Programming 4 Assignment", font);
	//to->SetPosition(80, 20);
	//scene.Add(to);
}

int main(int, char* []) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}
