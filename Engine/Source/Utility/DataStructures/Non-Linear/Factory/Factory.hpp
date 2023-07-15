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
		ReturnType* Build(const Identifier& aType, Args&&... args);
	//	ReturnType* Build(const Identifier& aType)												const;	// Perfect forward`??

		bool		HasComponent(const Identifier& aType)										const;

		bool		RegisterBuilder(const Identifier& aType, BuilderType* aBuilder);
		void		RemoveBuilder(const Identifier& aType);
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
	ReturnType* Factory<BuilderType, ReturnType, Identifier>::Build(const Identifier& aType, Args&&... args)
	{
		assert(HasComponent(aType) && "No Builder for type found!");
		return m_builders.at(aType)->Build(std::forward<Args>(args)...);
	}

	//template <typename BuilderType, typename ReturnType, typename Identifier>
	//ReturnType* Factory<BuilderType, ReturnType, Identifier>::Build(const Identifier& aType) const
	//{
	//	assert(HasComponent(aType) && "No Builder for type found!");
	//	return m_builders.at(aType)->Build();
	//}

	template <typename BuilderType, typename ReturnType, typename Identifier>
	bool Factory<BuilderType, ReturnType, Identifier>::HasComponent(const Identifier& aType) const
	{
		return m_builders.find(aType) != m_builders.end();
	}

	template <typename BuilderType, typename ReturnType, typename Identifier>
	bool Factory<BuilderType, ReturnType, Identifier>::RegisterBuilder(const Identifier& aType, BuilderType* aBuilder)
	{
		assert(aBuilder && "Can't register a Builder containing a nullptr");	// TODO; dont assert??

		return !HasComponent(aType) ? m_builders.insert({ aType, aBuilder }).second : false;
	}

	template <typename BuilderType, typename ReturnType, typename Identifier>
	void Factory<BuilderType, ReturnType, Identifier>::RemoveBuilder(const Identifier& aType)
	{
		if (HasComponent(aType))	// Check if needed??!
		{
			delete m_builders[aType];
			m_builders[aType] = nullptr; // Delete as well??
			m_builders.erase(aType);
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