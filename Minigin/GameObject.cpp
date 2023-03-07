#include "GameObject.h"
#include "RenderComponent.h"

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

void dae::GameObject::Render() const
{
	if (!m_pRenderComponent) return;
	m_pRenderComponent->Render();
}

void dae::GameObject::SetParent(GameObject* parent)
{
	// Check if the parent is not the same as the current parent and if the parent is not nullptr
	if (parent == m_pParent) return;

	//if (!parent)
	//{
	//	// Set the world position to the local position
	//	m_pTransformComponent->SetPosition(m_pTransformComponent->GetLocalPosition());
	//	// Remove this from the parent's children
	//	m_pParent->RemoveChild(this);
	//	// Set the parent to nullptr
	//	m_pParent = nullptr;
	//	return;
	//}

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
	//auto iter = std::find_if(m_Children.begin(), m_Children.end(), [child](GameObject* obj) {
	//	return obj == child;
	//	});
	//if (iter != m_Children.end())
	//{
	//	m_Children.erase(iter);
	//	child->m_pParent = nullptr;
	//}

	//// Get the child's transform component
	//auto childTransform{ child->GetTransformComponent() };
	//if (!childTransform) return;

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
