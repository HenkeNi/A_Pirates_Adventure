#pragma once

namespace Hi_Engine
{
	class IService;

	class ServiceFactory
	{
	public:
		static ServiceFactory& GetInstance();

		template <DerivedFrom<IService> T>
		void Register(const char* name);

		template <DerivedFrom<IService> T>
		[[nodiscard]] std::shared_ptr<T> Create(const char* type) const;

	private:
		using CreatorFunc = std::function<std::shared_ptr<IService>()>;

		//template <typename... Args>
		//std::shared_ptr<IService> CreatorFunc(Args&&... args);

		std::unordered_map<std::string, CreatorFunc> m_creators;
	};

#pragma region Templated_Methods

	template <DerivedFrom<IService> T>
	void ServiceFactory::Register(const char* name)
	{
		m_creators.insert_or_assign(name, []() { return std::make_shared<T>(); });
	}

	template <DerivedFrom<IService> T>
	std::shared_ptr<T> ServiceFactory::Create(const char* type) const
	{
		if (auto it = m_creators.find(type); it != m_creators.end())
		{
			return static_pointer_cast<T>(it->second());
		}

		return nullptr;
	}

#pragma endregion
}

// todo, cahce created component views? make views listen to entity created/destrpyed event?