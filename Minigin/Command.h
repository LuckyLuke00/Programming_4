#pragma once

// TODO: No gameobject is needed
// TODO: Don't make undo pure virtual, make it optional
namespace dae
{
	class GameObject;

	class Command
	{
	public:
		explicit Command(GameObject* gameObject);
		virtual ~Command() = default;

		Command(const Command& other) = delete;
		Command(Command&& other) noexcept = delete;
		Command& operator=(const Command& other) = delete;
		Command& operator=(Command&& other) noexcept = delete;

		virtual void Execute() = 0;
		virtual void Undo() = 0;
	protected:
		GameObject* GetGameObject() const { return m_GameObject; }
	private:
		GameObject* m_GameObject{ nullptr };
	};
}
