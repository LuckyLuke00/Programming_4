#pragma once
#include "Singleton.h"
#include <unordered_map>
#include <functional>

namespace dae
{
	class Event final
	{
	public:
		explicit Event(const char* name) : m_Name{ name } {}
		~Event() = default;

		Event(const Event& other) = delete;
		Event(Event&& other) noexcept = delete;
		Event& operator=(const Event& other) = delete;
		Event& operator=(Event&& other) noexcept = delete;

		const char* GetName() const { return m_Name; }
	private:
		const char* m_Name;
	};

	class EventManager final : public Singleton<EventManager>
	{
	public:
		void Subscribe(const char* name, std::function<void(Event*)> callback)
		{
			m_EventMap.insert_or_assign(name, callback);
		}

		void Unsubscribe(const char* name)
		{
			m_EventMap.erase(name);
		}

		void Notify(Event* event)
		{
			if (m_EventMap.contains(event->GetName()))
			{
				m_EventMap[event->GetName()](event);
			}
		}

	private:
		explicit EventManager() = default;
		std::unordered_map<const char*, std::function<void(Event*)>> m_EventMap;
	};
}
