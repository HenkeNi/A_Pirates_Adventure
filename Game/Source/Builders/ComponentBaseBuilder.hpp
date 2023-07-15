#pragma once
//#include "Components.h"
//#include <Core/Resources/ResourceHolder.hpp>

#include "ComponentInitializer.h"

// Rename ComponentBuilder?


class ComponentBase;

class ComponentBaseBuilder
{
public:
	virtual ~ComponentBaseBuilder() = default;
	//virtual ComponentBase* Build() const = 0;
	virtual ComponentBase* Build(std::unordered_map<std::string, std::any> someData) = 0;	// perfect forwarding instead?
};

template <typename T>
class ConcreteComponentBuilder : public ComponentBaseBuilder
{
public:
	//ComponentBase* Build() const override
	//{
	//	 return CU::MemoryPool<T>::GetInstance().GetResource();		// Have Init function in Component?  
	//}

	ComponentBase* Build(std::unordered_map<std::string, std::any> someData) override
	{
		T* component = CU::MemoryPool<T>::GetInstance().GetResource();
		ComponentInitializer::InitializeComponent(component, someData);	// HERE???

		return component;
	}
};

// Derived component builders??