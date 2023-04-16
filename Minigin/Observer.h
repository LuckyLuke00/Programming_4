#pragma once

namespace dae
{
	template <class T>
	class Observer
	{
	public:
		virtual ~Observer() = default;
		virtual void OnNotify(const T& event) = 0;

		Observer(const Observer& other) = delete;
		Observer(Observer&& other) noexcept = delete;
		Observer& operator=(const Observer& other) = delete;
		Observer& operator=(Observer&& other) noexcept = delete;

		// Getter for the observer
		virtual Observer<T>* GetObserver() = 0;

	protected:
		explicit Observer() = default;
	};
}
