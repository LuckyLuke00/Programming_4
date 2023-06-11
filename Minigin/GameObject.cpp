#include "GameObject.h"
#include "RenderComponent.h"
#include "RenderSpriteComponent.h"
#include "SceneManager.h"
#include "Scene.h"

void dae::GameObject::Update()
{
	if (!m_IsActive) return;

	// TODO: Update children
	for (const auto& [key, component] : m_Components)
	{
		// If nullptr, skip
		if (!component) continue;

		component->Update();
	}
}

void dae::GameObject::FixedUpdate()
{
	if (!m_IsActive) return;

	for (const auto& [key, component] : m_Components)
	{
		component->FixedUpdate();
	}
}

void dae::GameObject::LateUpdate()
{
	if (!m_IsActive) return;

	for (const auto& [key, component] : m_Components)
	{
		component->LateUpdate();
	}
}

void dae::GameObject::Render() const
{
	if (!m_IsActive) return;

	if (!m_pRenderComponent) return;
	m_pRenderComponent->Render();
}

void dae::GameObject::SetParent(GameObject* parent)
{
	// Check if the parent is not the same as the current parent and if the parent is not nullptr
	if (parent == m_pParent) return;

	// If a parent is already set, remove this from the parent's children
	if (m_pParent) m_pParent->RemoveChild(this);

	// Set the parent
	m_pParent = parent;

	// Add this to the parent's children
	m_pParent->AddChild(this);

	// Get the parent's transform component
	auto parentTransform{ m_pParent->GetTransformComponent() };
	if (!parentTransform) return;

	// Set the tranform
	m_pTransformComponent->SetPosition(m_pTransformComponent->GetLocalPosition() - parentTransform->GetWorldPosition());
}

void dae::GameObject::AddChild(GameObject* child)
{
	// Check if the child already has a parent
	if (child->GetParent())
	{
		// Remove the child from the parent's children
		child->GetParent()->RemoveChild(child);
	}

	// Set the child's parent to this
	child->SetParent(this);

	m_Children.emplace_back(child);
}

void dae::GameObject::RemoveChild(GameObject* child)
{
	auto iter{ std::find(m_Children.begin(), m_Children.end(), child) };
	if (iter != m_Children.end())
	{
		// Update the child's local position so that it stays in the same position in world space
		child->GetTransformComponent()->SetPosition(child->GetTransformComponent()->GetWorldPosition());
		// Remove the child from the parent's children
		m_Children.erase(iter);
		// Set the child's parent to nullptr
		child->m_pParent = nullptr;
	}
}

void dae::GameObject::SetRenderOrder(int order)
{
	m_RenderOrder = order;
	SceneManager::GetInstance().GetActiveScene()->SortObjects();
}
