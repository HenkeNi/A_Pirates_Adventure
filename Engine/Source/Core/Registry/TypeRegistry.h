#pragma once
#include "../../Services/IService.h"
#include "RegistryTraits.h"

namespace Hi_Engine
{
	// How to make work with Prefab(s) -> or store prefabs in ResourceHolder?+
	// replace wih curios recuring pattenr?
	// put in registry folder?

	// TODO; expand to use string as well (as key)?

	template <typename RegistryEntry, typename ID>
	class TypeRegistry : public IService
	{
	public:
		template <typename T, typename... Args>
		requires RegistryTraits<RegistryEntry>::template IsValidType<T> // maybe redundant?
		void Register(const std::string& name, ID id, Args&&... args); // or pass in both name and id as templated arguments??? optional ID?

		template <IsExactly<RegistryEntry> T>
		void Insert(const std::string& name, ID id, T&& entry); // string view?

		//void Remove(ID id);

		void RemoveAll();

		[[nodiscard]] const RegistryEntry& Get(ID id) const;
		[[nodiscard]] const RegistryEntry* TryGet(ID id) const;

		[[nodiscard]] const RegistryEntry& Get(const std::string& name) const; // use string_view instead?
		[[nodiscard]] const RegistryEntry* TryGet(const std::string& name) const;

		[[nodiscard]] bool IsRegistered(ID id) const noexcept;

		[[nodiscard]] bool IsRegistered(const std::string& name) const noexcept; // string view?

	private:
		// Primary Storage
		std::vector<RegistryEntry> m_entries;

		// Lookup (TODO; combine into a single map? - user provides valid ID/key)
		std::unordered_map<ID, std::size_t> m_idToIndex;
		std::unordered_map<std::string, std::size_t> m_nameToIndex; // just use one? ID or name? (if so, use SparseSet?)
	};

#pragma region Templated_Methods

	template <typename RegistryEntry, typename ID>
	template <typename T, typename... Args>
	requires RegistryTraits<RegistryEntry>::template IsValidType<T>
	void TypeRegistry<RegistryEntry, ID>::Register(const std::string& name, ID id, Args&&... args)
	{
		auto& entry = m_entries.emplace_back(std::forward<Args>(args)...);

		std::size_t index = m_entries.size() - 1;

		m_idToIndex.insert({ id, index });
		m_nameToIndex.insert({ name, index });
	}

	template <typename RegistryEntry, typename ID>
	template <IsExactly<RegistryEntry> T>
	void TypeRegistry<RegistryEntry, ID>::Insert(const std::string& name, ID id, T&& entry)
	{
		m_entries.push_back(std::forward<T>(entry));

		std::size_t index = m_entries.size() - 1;

		m_idToIndex.insert({ id, index });
		m_nameToIndex.insert({ name, index });
	}

	template <typename RegistryEntry, typename ID>
	void TypeRegistry<RegistryEntry, ID>::RemoveAll()
	{
		m_entries.clear();
		m_idToIndex.clear();
		m_nameToIndex.clear();
	}

	template <typename RegistryEntry, typename ID>
	const RegistryEntry& TypeRegistry<RegistryEntry, ID>::Get(ID id) const
	{
		if (auto it = m_idToIndex.find(id); it != m_idToIndex.end())
		{
			std::size_t index = it->second;

			if (index >= 0 && index < m_entries.size())
				return m_entries.at(index);
		}

		throw std::runtime_error("Entry not found!");
	}
	
	template <typename RegistryEntry, typename ID>
	const RegistryEntry* TypeRegistry<RegistryEntry, ID>::TryGet(ID id) const
	{
		if (auto it = m_idToIndex.find(id); it != m_idToIndex.end())
		{
			std::size_t index = it->second;

			if (index >= 0 && index < m_entries.size())
				return &m_entries.at(index);
		}

		return nullptr;
	}

	template <typename RegistryEntry, typename ID>
	const RegistryEntry& TypeRegistry<RegistryEntry, ID>::Get(const std::string& name) const
	{
		if (auto it = m_nameToIndex.find(name); it != m_nameToIndex.end())
		{
			std::size_t index = it->second;

			if (index >= 0 && index < m_entries.size())
				return m_entries.at(index);
		}

		throw std::runtime_error("Entry not found!");
	}

	template <typename RegistryEntry, typename ID>
	const RegistryEntry* TypeRegistry<RegistryEntry, ID>::TryGet(const std::string& name) const
	{
		if (auto it = m_nameToIndex.find(name); it != m_nameToIndex.end())
		{
			std::size_t index = it->second;

			if (index >= 0 && index < m_entries.size())
				return &m_entries.at(index);
		}

		return nullptr;
	}

	template <typename RegistryEntry, typename ID>
	bool TypeRegistry<RegistryEntry, ID>::IsRegistered(ID id) const noexcept
	{
		return m_idToIndex.contains(id);
	}

	template<typename RegistryEntry, typename ID>
	inline bool TypeRegistry<RegistryEntry, ID>::IsRegistered(const std::string& name) const noexcept
	{
		return m_nameToIndex.contains(name);
	}

#pragma endregion
}
