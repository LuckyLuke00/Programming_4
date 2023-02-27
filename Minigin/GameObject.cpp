#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

void dae::GameObject::Update()
{
	for (const auto& [key, component] : m_Components)
	{
		component->Update();
	}
}

void dae::GameObject::FixedUpdate()
{
	for (const auto& [key, component] : m_Components)
	{
		component->FixedUpdate();
	}
}

void dae::GameObject::LateUpdate()
{
	for (const auto& [key, component] : m_Components)
	{
		component->LateUpdate();
	}
}
