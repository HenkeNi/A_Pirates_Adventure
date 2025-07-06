#pragma once

namespace Hi_Engine
{
	class IService;

	struct ServiceDefinition
	{
		//std::function<std::shared_ptr<IService>(const std::unordered_map<std::type_index, std::shared_ptr<IService>>&)> Factory;
		std::function<std::shared_ptr<IService>(const std::unordered_map<std::type_index, std::shared_ptr<IService>>&)> Factory;
		std::vector<std::type_index> Dependencies;
	};

	class ServiceGraph
	{
	public:
		template <DerivedFrom<IService> Service, DerivedFrom<IService>... Dependencies>
		void Register();

		std::unordered_map<std::type_index, std::shared_ptr<IService>> Build();

	private:
		template <DerivedFrom<IService> T>
		constexpr std::type_index GetTypeIndex() const noexcept;

		std::vector<std::type_index> TopologicalSort() const;

		std::unordered_map<std::type_index, ServiceDefinition> m_definitions;
	};

#pragma region Templated_Method

	template <DerivedFrom<IService> Service, DerivedFrom<IService>... Dependencies>
	void ServiceGraph::Register()
	{
		ServiceDefinition def;
		(def.Dependencies.push_back(GetTypeIndex<Dependencies>()), ...);
		def.Factory = [&](const auto& services) { return std::make_shared<Service>(std::static_pointer_cast<Dependencies>(services.at(GetTypeIndex<Dependencies>()))...); };

		m_definitions.insert({ GetTypeIndex<Service>(), std::move(def) });
	}

	template <DerivedFrom<IService> T>
	constexpr std::type_index ServiceGraph::GetTypeIndex() const noexcept
	{
		return std::type_index(typeid(T));
	}

#pragma endregion
}