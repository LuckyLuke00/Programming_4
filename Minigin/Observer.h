#pragma once

namespace dae
{
	template<typename... Args>
	class Observer
	{
	public:
		virtual ~Observer() = default;
		virtual void OnNotify(Args... args) = 0;
		virtual void OnSubjectDestroy() = 0;
	};
}
