#pragma once
#include "Transform.h"
#include <memory>
#include <string>
#include "TransformComponent.h"
#include <unordered_map>
#include <typeindex>

namespace dae
{
	class Texture2D;
	class Component;

	class GameObject final
	{
	public:
		virtual void Update();

		template <typename T> T* GetComponent() const;
		template <typename T> T* AddComponent();
		template <typename T> void RemoveComponent();

		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) noexcept = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) noexcept = delete;

	private:
		std::unordered_map<std::type_index, std::shared_ptr<Component>> m_Components{};
	};

	template<typename T>
	inline T* GameObject::GetComponent() const
	{
		auto iter = m_Components.find(typeid(T));
		if (iter != m_Components.end())
		{
			return dynamic_cast<T*>(iter->second.get());
		}
		else
		{
			return nullptr;
		}
	}

	template<typename T>
	inline T* GameObject::AddComponent()
	{
		auto component = std::make_shared<T>(this);
		m_Components[typeid(T)] = component;
		return component.get();
	}

	template<typename T>
	inline void GameObject::RemoveComponent()
	{
		m_Components.erase(typeid(T));
	}
}
