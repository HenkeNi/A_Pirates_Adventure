#pragma once
#include "ComponentInitializer.h"

class Component;

class ComponentBuilder
{
public:
	virtual ~ComponentBuilder() = default;

	virtual Component* Build(std::unordered_map<std::string, std::any> data) = 0; // just std;;any?
};

template <typename T>
class ConcreteComponentBuilder : public ComponentBuilder
{
public:
	Component* Build(std::unordered_map<std::string, std::any> data) override
	{
		T* component = Hi_Engine::MemoryPool<T>::GetInstance().GetResource();
		ComponentInitializer::InitializeComponent(component, data);	// HERE???

		return component;
	}
};