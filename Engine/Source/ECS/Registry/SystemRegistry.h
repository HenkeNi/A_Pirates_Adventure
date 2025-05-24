#pragma once
#include "../Utility/ECSTypes.h"

namespace Hi_Engine
{
	class System;

	struct SystemRegistryEntry
	{
		std::function<std::unique_ptr<System>()> CreatorFunction;
		const char* DisplayName;

		bool IsEnabledByDefault = true;
		SystemID ID;

		// Update order? enum / tag for type (render, physics, logic)? Dependencies
		// Execution / Update phase: PreUpdate, Update, PostUpdate
	};

	class SystemRegistry
	{
	public:
		template <DerivedFrom<System> T>
		void Register(const char* type);

		[[nodiscard]] const std::function<std::unique_ptr<System>()>& GetCreator(const char* type) const;

		template <DerivedFrom<System> T>
		[[nodiscard]] bool IsRegistered() const;
		
		[[nodiscard]] bool IsRegistered(const char* type) const;
	
		template <DerivedFrom<System> T>
		[[nodiscard]] SystemID GetSystemID() const noexcept;

	private:
		[[nodiscard]] SystemID GenerateID() const noexcept;

		// key: type index? or genereate id? string? or have multiple maps (see component registry)?
		std::unordered_map<std::string, SystemRegistryEntry> m_entries; // rename?
		std::unordered_map<std::type_index, SystemRegistryEntry*> m_typeToEntry;
	};

#pragma region Templated_Methods

	template <DerivedFrom<System> T>
	void SystemRegistry::Register(const char* type)
	{
		SystemRegistryEntry entry;
		entry.DisplayName = type;
		entry.CreatorFunction = []() { return std::make_unique<T>(); };
		entry.ID = GetSystemID<T>();
		
		auto [it, success] = m_entries.insert_or_assign(type, std::move(entry));

		if (success)
			m_typeToEntry.insert_or_assign(std::type_index(typeid(T)), &it->second);
	}

	template <DerivedFrom<System> T>
	bool SystemRegistry::IsRegistered() const
	{
		return false;
	}

	//template <DerivedFrom<System> T>
	//SystemID SystemRegistry::GetSystemID() const noexcept
	//{
	//	//static 
	//	return SystemID();
	//}

#pragma endregion
}