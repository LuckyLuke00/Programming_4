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
			m_Observers.erase(std::remove(m_Observers.begin(), m_Observers.end(), observer), m_Observers.end());
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
