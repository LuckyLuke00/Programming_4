#pragma once
#include "Observer.h"
#include <vector>
#include <algorithm>

namespace dae
{
	template <class T>
	class Subject
	{
	public:
		virtual ~Subject() = default;
		void AddObserver(Observer<T>* pObserver)
		{
			m_pObservers.push_back(pObserver);
		}

		void RemoveObserver(Observer<T>* pObserver)
		{
			m_pObservers.erase(std::ranges::remove(m_pObservers, pObserver), m_pObservers.end());
		}

		void Notify(T data) const
		{
			for (Observer<T>* pObserver : m_pObservers)
			{
				pObserver->OnNotify(data);
			}
		}

		Subject(const Subject& other) = delete;
		Subject(Subject&& other) noexcept = delete;
		Subject& operator=(const Subject& other) = delete;
		Subject& operator=(Subject&& other) noexcept = delete;

	protected:
		explicit Subject() = default;

	private:
		std::vector<Observer<T>*> m_pObservers;
	};
}
