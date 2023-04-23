#pragma once

class Component;

class ComponentBuilder
{
public:
	virtual ~ComponentBuilder() = default;
	virtual Component* Build() const = 0;
};

template <typename T>
class ConcreteComponentBuilder : public ComponentBuilder  //DerivedComponentBuilder
{
public:
	Component* Build() const override
	{
		return new T{}; // Placement new??
	}
};