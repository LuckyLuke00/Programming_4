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

		virtual void Update();
		virtual void FixedUpdate();
		virtual void LateUpdate();

	protected:
		explicit Component(GameObject* pOwner);
		GameObject* GetOwner() const { return m_pOwner; }

	private:
		GameObject* m_pOwner{ nullptr };
	};
}
