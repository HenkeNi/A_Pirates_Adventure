#pragma once
#include <../../Engine/Source/Core/Utility/DataStructures/Linear/Static/MemoryPool/MemoryPool.hpp>
#include "Systems.h"

class System;

class SystemBuilder
{
public:
	virtual ~SystemBuilder() = default;

	//virtual std::unique_ptr<System> Build() = 0;
	virtual System* Build() = 0;
};

template <typename T>
class ConcreteSystemBuilder : public SystemBuilder
{
public:
	//std::unique_ptr<System> Build() override
	System* Build() override
	{
		//T* system = std::make_unique<T>();
		//T* system = Hi_Engine::MemoryPool<T>::GetInstance().GetResource(); // dibt use memory pool here???
		return new T;
	}
};