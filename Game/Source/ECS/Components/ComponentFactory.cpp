#include "Pch.h"
#include "ComponentFactory.h"

ComponentFactory::ComponentFactory()
{
}

ComponentFactory::~ComponentFactory()
{
	Clear();
}

bool ComponentFactory::HasBuilder(const std::string& type) const
{
	return m_builders.find(type) != m_builders.end();
}

bool ComponentFactory::RegisterBuilder(const std::string& type, ComponentBuilder* builder)
{
	assert(builder && "Can't register a Builder containing a nullptr");

	return !HasBuilder(type) ? m_builders.insert({ type, builder }).second : false;
}

void ComponentFactory::RemoveBuilder(const std::string& type)
{
	if (HasBuilder(type))	// Check if needed??!
	{
		delete m_builders[type];
		m_builders[type] = nullptr; // Delete as well??
		m_builders.erase(type);
	}
}

void ComponentFactory::Clear()
{
	for (auto builder : m_builders)
		delete builder.second;
}