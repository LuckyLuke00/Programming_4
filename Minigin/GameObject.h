#pragma once
#include <memory>
#include "TransformComponent.h"
#include <unordered_map>
#include <typeindex>
#include <string>

namespace dae
{
	class Texture2D;
	class Component;
	class RenderComponent;

	class GameObject final
	{
	public:
		GameObject() = default;
		~GameObject() = default;
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) noexcept = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) noexcept = delete;

		void Update();
		void FixedUpdate();
		void LateUpdate();

		void Render() const;

		void SetParent(GameObject* parent);
		GameObject* GetParent() const { return m_pParent; }

		void AddChild(GameObject* child);
		void RemoveChild(GameObject* child);

		void SetActive(bool isActive) { m_IsActive = isActive; }
		bool IsActive() const { return m_IsActive; }

		void SetRenderOrder(int order) { m_RenderOrder = order; }
		int GetRenderOrder() const { return m_RenderOrder; }

		void MarkForDelete() { m_MarkedForDelete = true; }
		bool IsMarkedForDelete() const { return m_MarkedForDelete; }

		void SetTag(const char* tag) { m_Tag = tag; }
		std::string GetTag() const { return m_Tag; }

		// Getters
		const std::vector<GameObject*>& GetChildren() const { return m_Children; }
		TransformComponent* GetTransformComponent() const { return m_pTransformComponent; }

		template <typename T> T* GetComponent() const;
		template <typename T> T* AddComponent();
		template <typename T> void RemoveComponent();
		template <typename T> bool HasComponent() const;

	private:
		std::string m_Tag{ "" };
		int m_RenderOrder{ 0 };
		bool m_MarkedForDelete{ false };
		bool m_IsActive{ true };
		GameObject* m_pParent{ nullptr };
		std::vector<GameObject*> m_Children{};

		std::unordered_map<std::type_index, std::shared_ptr<Component>> m_Components{};
		RenderComponent* m_pRenderComponent{ nullptr };
		TransformComponent* m_pTransformComponent{ nullptr };
	};

	template<typename T>
	inline T* GameObject::GetComponent() const
	{
		//if (const auto iter{ m_Components.find(typeid(T)) }; iter != m_Components.end())
		//{
		//	return dynamic_cast<T*>(iter->second.get());
		//}
		//return nullptr;

		// With this we can get base class components from derived classes
		for (const auto& [type, component] : m_Components)
		{
			if (const auto castedComponent{ dynamic_cast<T*>(component.get()) })
			{
				return castedComponent;
			}
		}
		return nullptr;
	}

	template<typename T>
	inline T* GameObject::AddComponent()
	{
		auto component{ std::make_unique<T>(this) };
		auto componentPtr{ component.get() };
		m_Components[typeid(T)] = std::move(component);

		if (auto renderComponent{ dynamic_cast<RenderComponent*>(componentPtr) })
		{
			m_pRenderComponent = renderComponent;
		}
		else if (auto transformComponent{ dynamic_cast<TransformComponent*>(componentPtr) })
		{
			m_pTransformComponent = transformComponent;
		}

		return componentPtr;
	}

	template<typename T>
	inline void GameObject::RemoveComponent()
	{
		m_Components.erase(typeid(T));
	}

	template<typename T>
	inline bool GameObject::HasComponent() const
	{
		return m_Components.contains(typeid(T));
	}
}
