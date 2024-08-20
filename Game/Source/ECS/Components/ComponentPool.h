#pragma once

class IComponentPool
{
public:
	~IComponentPool() = default;
	virtual void ReturnResource(void* resource) = 0;
};

template <typename T, typename SizeType = unsigned, SizeType size = 1024>
class ComponentPool : public IComponentPool
{
public:
	ComponentPool();
	~ComponentPool();

	void ReturnResource(void* resource) override;
	T* GetResource();
	bool IsEmpty() const;

private:
	T* m_resources;
	std::stack<T*>	m_available;
};

#pragma region Method_Definitions

template<typename T, typename SizeType, SizeType size>
ComponentPool<T, SizeType, size>::ComponentPool()
	: m_resources{ new T[size] }
{
	for (int i = 0; i < size; ++i)
	{
		m_available.push(&m_resources[i]);
	}
}

template<typename T, typename SizeType, SizeType size>
ComponentPool<T, SizeType, size>::~ComponentPool()
{
	delete[] m_resources;
}

template<typename T, typename SizeType, SizeType size>
T* ComponentPool<T, SizeType, size>::GetResource()
{
	assert(!IsEmpty() && "Component pool reached out of resources!"); // Retur nullptr?
	
	auto* resource = m_available.top();
	m_available.pop();
	
	return resource;
}

template<typename T, typename SizeType, SizeType size>
void ComponentPool<T, SizeType, size>::ReturnResource(void* resource)
{
	if (resource)
	{
		m_available.push(static_cast<T*>(resource));
	}
}

template<typename T, typename SizeType, SizeType size>
bool ComponentPool<T, SizeType, size>::IsEmpty() const
{
	return m_available.empty();
}

#pragma endregion Method_Definitions