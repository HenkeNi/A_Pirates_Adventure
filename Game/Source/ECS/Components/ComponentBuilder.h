#pragma once
#include "ComponentInitializer.h"

class Component;

class ComponentBuilder
{
public:
	virtual ~ComponentBuilder() = default;

	virtual Component* Build(std::unordered_map<std::string, std::any> someData) = 0; // just std;;any?
};

template <typename T>
class ConcreteComponentBuilder : public ComponentBuilder
{
public:
	Component* Build(std::unordered_map<std::string, std::any> someData) override
	{
		T* component = CU::MemoryPool<T>::GetInstance().GetResource();
		ComponentInitializer::InitializeComponent(component, someData);	// HERE???

		return component;
	}
};