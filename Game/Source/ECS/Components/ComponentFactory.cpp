#include "Pch.h"
#include "ComponentFactory.h"

//ComponentFactory::ComponentFactory()
//{
//}
//
//ComponentFactory::~ComponentFactory()
//{
//	Clear();
//}
//
//bool ComponentFactory::HasBuilder(const std::string& aType) const
//{
//	return m_builders.find(aType) != m_builders.end();
//}
//
//bool ComponentFactory::RegisterBuilder(const std::string& aType, ComponentBuilder* aBuilder)
//{
//	assert(aBuilder && "Can't register a Builder containing a nullptr");
//
//	return !HasBuilder(aType) ? m_builders.insert({ aType, aBuilder }).second : false;
//}
//
//void ComponentFactory::RemoveBuilder(const std::string& aType)
//{
//	if (HasBuilder(aType))	// Check if needed??!
//	{
//		delete m_builders[aType];
//		m_builders[aType] = nullptr; // Delete as well??
//		m_builders.erase(aType);
//	}
//}
//
//void ComponentFactory::Clear()
//{
//	for (auto builder : m_builders)
//		delete builder.second;
//}