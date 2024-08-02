#pragma once

// constatns namespcae??

constexpr std::size_t MaxSystems = 64;
constexpr std::size_t MaxEntities = 5000;

constexpr std::uint8_t MaxComponents = 64; // increase when adding more components?

using Signature = std::bitset<MaxComponents>;
using Signatures = std::unordered_map<std::string, Signature>;

using Entity = int;

using ComponentType = std::uint8_t;
using ComponentTypes = std::unordered_map<std::type_index, ComponentType>;

using Property = std::variant<bool, int, float, double, std::string, FVector2, FVector3, FVector4, IVector2, IVector3, IVector4>;
using ComponentProperties = std::unordered_map<std::string, Property>;

using ComponentArrays = std::unordered_map<std::type_index, std::unique_ptr<class IComponentArray>>;
using ComponentPools = std::unordered_map<std::type_index, std::unique_ptr<class IComponentPool>>;

struct ComponentRegistryEntry
{
	std::function<void(Entity)> AddComponent;
	std::function<void(Entity, const ComponentProperties&)> InitializeComponent;
};

using ComponentRegistry = std::unordered_map<std::string, ComponentRegistryEntry>;
