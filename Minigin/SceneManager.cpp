#include "SceneManager.h"
#include "Scene.h"

void dae::SceneManager::Update()
{
	for (const auto& scene : m_scenes)
	{
		scene->Update();
	}
}

void dae::SceneManager::FixedUpdate()
{
	for (const auto& scene : m_scenes)
	{
		scene->FixedUpdate();
	}
}

void dae::SceneManager::LateUpdate()
{
	for (const auto& scene : m_scenes)
	{
		scene->LateUpdate();
	}
}

void dae::SceneManager::Render()
{
	for (const auto& scene : m_scenes)
	{
		scene->Render();
	}
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	const auto& scene{ std::shared_ptr<Scene>(new Scene(name)) };
	m_scenes.emplace_back(scene);
	return *scene;
}

void dae::SceneManager::CleanUp()
{
	for (const auto& scene : m_scenes)
	{
		scene->CleanUp();
	}
}
