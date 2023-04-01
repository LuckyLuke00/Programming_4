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

#define DEMO_SCENE
#define FPS_COUNTER

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
	fpsTextComponent->SetColor({ 255, 255, 0, 255 });

	fps->AddComponent<dae::FPSComponent>();

	demoScene.Add(std::move(fps));

#endif // FPS_COUNTER

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
