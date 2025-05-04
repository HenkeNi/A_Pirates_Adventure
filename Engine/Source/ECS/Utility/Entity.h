#pragma once
#include <cstdint>
#include <cstddef>
#include <functional>

namespace Hi_Engine
{
	using EntityID = uint32_t;

	struct Entity
	{
		EntityID ID; // or index
		uint32_t Version;
	};

	struct EntityEqual
	{
		bool operator()(const Entity& lhs, const Entity& rhs)
		{
			return lhs.ID == rhs.ID && lhs.Version == rhs.Version;
		}
	};

	struct EntityHash 
	{
		std::size_t operator()(const Entity& e) const 
		{
			std::size_t h1 = std::hash<uint32_t>{}(e.ID);
			std::size_t h2 = std::hash<uint32_t>{}(e.Version);

			return h1 ^ (h2 + 0x9e3779b9 + (h1 << 6) + (h1 >> 2));
		}
	};
}