#pragma once
#include <memory>
#include <string>
#include "TransformComponent.h"
#include <unordered_map>
#include <typeindex>

namespace dae
{
	class Texture2D;
	class Component;
	class RenderComponent;

	class GameObject final
	{
	public:
		void Update();
		void FixedUpdate();
		void LateUpdate();

		void Render() const;

		template <typename T> T* GetComponent() const;
		template <typename T> T* AddComponent();
		template <typename T> void RemoveComponent();
		template <typename T> bool HasComponent() const;

		GameObject() = default;
		~GameObject() = default;
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) noexcept = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) noexcept = delete;

	private:
		std::unordered_map<std::type_index, std::shared_ptr<Component>> m_Components{};
		RenderComponent* m_pRenderComponent{ nullptr };
	};

	template<typename T>
	inline T* GameObject::GetComponent() const
	{
		const auto iter{ m_Components.find(typeid(T)) };
		if (iter != m_Components.end())
		{
			return dynamic_cast<T*>(iter->second.get());
		}
		return nullptr;
	}

	template<typename T>
	inline T* GameObject::AddComponent()
	{
		const auto component{ std::make_shared<T>(this) };
		m_Components[typeid(T)] = component;

		// Store pointer to the RenderComponent if it's added
		if (typeid(T) == typeid(RenderComponent))
		{
			m_pRenderComponent = dynamic_cast<RenderComponent*>(component.get());
		}

		return component.get();
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
