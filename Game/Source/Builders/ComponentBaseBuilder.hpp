#pragma once

class ComponentBase;

class ComponentBaseBuilder
{
public:
	virtual ~ComponentBaseBuilder() = default;
	virtual ComponentBase* Build() const = 0;
};

// change name to DerivedComponentBuilder??
template <typename T>
class ConcreteComponentBuilder : public ComponentBaseBuilder
{
public:
	ComponentBase* Build() const override
	{
		return CU::MemoryPool<T>::GetInstance().GetResource();
		//return new T{};
	}
};