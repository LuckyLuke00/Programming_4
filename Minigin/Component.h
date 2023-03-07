#pragma once

namespace dae
{
	class GameObject;

	class Component
	{
	public:
		virtual ~Component() = default;

		Component(const Component& other) = delete;
		Component(Component&& other) noexcept = delete;
		Component& operator=(const Component& other) = delete;
		Component& operator=(Component&& other) noexcept = delete;

		virtual void Update() = 0;
		virtual void FixedUpdate() = 0;
		virtual void LateUpdate() = 0;

	protected:
		explicit Component(GameObject* pOwner);
		GameObject* GetOwner() const { return m_pOwner; }

	private:
		GameObject* m_pOwner{ nullptr };
	};
}
