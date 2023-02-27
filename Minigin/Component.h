#pragma once

namespace dae
{
	class GameObject;

	class Component
	{
	public:
		explicit Component(const GameObject* pOwner);
		virtual ~Component() = default;

		Component(const Component& other) = delete;
		Component(Component&& other) noexcept = delete;
		Component& operator=(const Component& other) = delete;
		Component& operator=(Component&& other) noexcept = delete;

		virtual void Update() = 0;

		const GameObject* GetOwner() const { return m_pOwner; }
	
	protected:
		const GameObject* m_pOwner{ nullptr };
	};
}

