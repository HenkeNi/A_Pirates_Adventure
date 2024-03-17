#pragma once
#include <string>
#include <unordered_map>

// TODO: rename all structures with a T infront? TArray, TFactory??

namespace CommonUtilities
{
	//template <typename Builder, typename Created, typename Identifier = std::string>
	template <typename BuilderType, typename ReturnType, typename Identifier = std::string>
	class Factory
	{
	public:
		Factory();
		~Factory();

		template	<typename... Args>
		ReturnType* Build(const Identifier& type, Args&&... args);
	//	ReturnType* Build(const Identifier& aType)												const;	// Perfect forward`??

		bool		HasResource(const Identifier& type)										const;

		bool		RegisterBuilder(const Identifier& type, BuilderType* builder);
		void		RemoveBuilder(const Identifier& type);
		void		Clear();

	private:
		std::unordered_map<Identifier, BuilderType*> m_builders;
	};

#pragma region Constructors

	template <typename BuilderType, typename ReturnType, typename Identifier>
	Factory<BuilderType, ReturnType, Identifier>::Factory()
	{
	}

	template <typename BuilderType, typename ReturnType, typename Identifier>
	Factory<BuilderType, ReturnType, Identifier>::~Factory()
	{
		Clear();
	}

#pragma endregion Constructors

#pragma region Method_Definitions

	template <typename BuilderType, typename ReturnType, typename Identifier>
	template <typename... Args>
	ReturnType* Factory<BuilderType, ReturnType, Identifier>::Build(const Identifier& type, Args&&... args)
	{
		assert(HasResource(type) && "No Builder for type found!");
		return m_builders.at(type)->Build(std::forward<Args>(args)...);
	}

	//template <typename BuilderType, typename ReturnType, typename Identifier>
	//ReturnType* Factory<BuilderType, ReturnType, Identifier>::Build(const Identifier& aType) const
	//{
	//	assert(HasComponent(aType) && "No Builder for type found!");
	//	return m_builders.at(aType)->Build();
	//}

	template <typename BuilderType, typename ReturnType, typename Identifier>
	bool Factory<BuilderType, ReturnType, Identifier>::HasResource(const Identifier& type) const
	{
		return m_builders.find(type) != m_builders.end();
	}

	template <typename BuilderType, typename ReturnType, typename Identifier>
	bool Factory<BuilderType, ReturnType, Identifier>::RegisterBuilder(const Identifier& type, BuilderType* builder)
	{
		assert(builder && "Can't register a Builder containing a nullptr");	// TODO; dont assert??

		return !HasResource(type) ? m_builders.insert({ type, builder }).second : false;
	}

	template <typename BuilderType, typename ReturnType, typename Identifier>
	void Factory<BuilderType, ReturnType, Identifier>::RemoveBuilder(const Identifier& type)
	{
		if (HasResource(type))	// Check if needed??!
		{
			delete m_builders[type];
			m_builders[type] = nullptr; // Delete as well??
			m_builders.erase(type);
		}
	}

	template <typename BuilderType, typename ReturnType, typename Identifier>
	void Factory<BuilderType, ReturnType, Identifier>::Clear()
	{
		for (auto builder : m_builders)
			delete builder.second;
	}

#pragma endregion Method_Definitions
}