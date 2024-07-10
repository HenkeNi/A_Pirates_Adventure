#pragma once
#include "ComponentInitializer.h"

class Component;

namespace
{
	using ComponentData = std::unordered_map<std::string, std::any>;
}

class ComponentBuilder
{
public:
	virtual ~ComponentBuilder() = default;

	virtual Component* Build(const ComponentData& data) = 0;
};

template <typename T>
class ConcreteComponentBuilder : public ComponentBuilder
{
public:
	Component* Build(const ComponentData& data) override
	{
		T* component = Hi_Engine::MemoryPool<T>::GetInstance().GetResource();
		ComponentInitializer::InitializeComponent(component, data);	// HERE??? try to pass in data instead?

		return component;
	}
};