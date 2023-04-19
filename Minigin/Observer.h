#pragma once

namespace dae
{
	template <typename T>
	class Observer
	{
	public:
		virtual ~Observer() = default;
		virtual void OnNotify(const T& data) = 0;

	protected:
		// When using a default constructor, the explicit keyword is not needed
		Observer() = default;
	};
}
