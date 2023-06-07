#include "Scene.h"
#include "GameObject.h"
#include <algorithm>

using namespace dae;

unsigned int Scene::m_idCounter = 0;

Scene::Scene(const std::string& name) : m_name(name) {}

void dae::Scene::SortObjects()
{
	// Move the objects with a lower render order to the front of the vector
	std::ranges::sort(m_objects, [](const std::shared_ptr<GameObject>& a, const std::shared_ptr<GameObject>& b)
		{
			return a->GetRenderOrder() < b->GetRenderOrder();
		});
}

Scene::~Scene() = default;

void Scene::Add(std::shared_ptr<GameObject> object)
{
	m_objects.emplace_back(std::move(object));
	SortObjects();
}

void Scene::Remove(std::shared_ptr<GameObject> object)
{
	auto it{ std::ranges::find(m_objects, object) };
	if (it != m_objects.end()) m_objects.erase(it);
}

void Scene::RemoveAll()
{
	m_objects.clear();
}

void Scene::Update()
{
	for (const auto& object : m_objects)
	{
		object->Update();
	}
}

void dae::Scene::FixedUpdate()
{
	for (const auto& object : m_objects)
	{
		object->FixedUpdate();
	}
}

void dae::Scene::LateUpdate()
{
	for (const auto& object : m_objects)
	{
		object->LateUpdate();
	}
}

void Scene::Render() const
{
	for (const auto& object : m_objects)
	{
		object->Render();
	}
}
