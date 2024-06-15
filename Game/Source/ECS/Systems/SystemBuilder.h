#pragma once

class System;

class SystemBuilder
{
public:
	virtual ~SystemBuilder() = default;

	virtual System* Build() = 0;
};

template <typename T>
class ConcreteSystemBuilder : public SystemBuilder
{
public:
	System* Build() override
	{
		// T* system = Hi_Engine::MemoryPool<T>::GetInstance().GetResource();
		return system;
	}
};