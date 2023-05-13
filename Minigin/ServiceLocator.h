#pragma once
#include <memory>

namespace dae
{
	template<typename T>
	class NullService;

	template<typename T>
	class ServiceLocator final
	{
	public:
		ServiceLocator(const ServiceLocator& other) = delete;
		ServiceLocator(ServiceLocator&& other) noexcept = delete;
		ServiceLocator& operator=(const ServiceLocator& other) = delete;
		ServiceLocator& operator=(ServiceLocator&& other) noexcept = delete;

		static T& GetService() { return *m_pService; }
		static void RegisterService(std::unique_ptr<T>&& service) { m_pService = std::move(service); }

	private:
		explicit ServiceLocator() = default;
		~ServiceLocator() = default;

		static std::unique_ptr<T> m_pService;
	};

	template<typename T>
	std::unique_ptr<T> ServiceLocator<T>::m_pService{ std::make_unique<NullService<T>>() };
}
