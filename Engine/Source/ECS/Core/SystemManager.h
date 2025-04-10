#pragma once

namespace Hi_Engine
{
	class System;

	class SystemManager
	{
	public:
		void AddSystem(std::shared_ptr<System>&& system);
		void ForEachSystem(const std::function<void(System&)>& callback);

	private:
		void SortSystems();

		using SystemRegistry = std::vector<std::shared_ptr<System>>;

		SystemRegistry m_systems;

		// std::unordered_map<std::string, std::type_index> m_systemTypes;
	};
}