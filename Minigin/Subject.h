#pragma once
#include <vector>
#include "Observer.h"

namespace dae
{
	template<typename... Args>
	class Subject
	{
	public:
		virtual ~Subject()
		{
			for (auto& observer : m_Observers)
			{
				observer->OnSubjectDestroy();
			}
		}

		void AddObserver(Observer<Args...>* observer)
		{
			m_Observers.emplace_back(observer);
		}

		void RemoveObserver(Observer<Args...>* observer)
		{
			if (m_Observers.empty()) return;
			auto it{ std::ranges::find(m_Observers, observer) };
			if (it != m_Observers.end()) m_Observers.erase(it);
		}

		void Notify(Args... args)
		{
			for (auto& observer : m_Observers)
			{
				observer->OnNotify(args...);
			}
		}

	private:
		std::vector<Observer<Args...>*> m_Observers;
	};
}
