#include "Pch.h"
#include "ServiceGraph.h"

namespace Hi_Engine
{
	std::unordered_map<std::type_index, std::shared_ptr<IService>> ServiceGraph::Build() const // safe to insert into unorderd:map?
	{
		std::unordered_map<std::type_index, std::shared_ptr<IService>> result;

		auto sorted = TopologicalSort();
		for (const auto& type : sorted)
		{
			const auto& def = m_definitions.at(type);
			result[type] = def.Factory(result);
		}

		return result;
	}

	std::vector<std::type_index> ServiceGraph::TopologicalSort() const
	{
		std::vector<std::type_index> sorted;
		std::unordered_set<std::type_index> visited;
		std::unordered_set<std::type_index> visiting; // unvisited?

		std::function<void(const std::type_index&)> visit = [&](const std::type_index& type)
			{
				if (visited.contains(type)) return;
				if (visiting.contains(type)) throw std::runtime_error("Circular dependency");

				visiting.insert(type);

				for (const auto& dependency : m_definitions.at(type).Dependencies)
				{
					visit(dependency);
				}

				visiting.erase(type);
				visited.insert(type);
				sorted.push_back(type);
			};

			
		for (const auto& [type, _] : m_definitions)
			visit(type);

		return sorted;
	}
}