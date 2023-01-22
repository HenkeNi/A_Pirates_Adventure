#pragma once
#include <cstddef>
#include <vector>


namespace CommonUtilities
{
	template <class Type, bool isStatic = true, typename SizeType = unsigned int, SizeType size = 56>
	class MemoryPool
	{
	public:
		MemoryPool();
		~MemoryPool();
		
		MemoryPool(const MemoryPool&)			= delete;
		MemoryPool& operator(const MemoryPool&) = delete;

		bool ReturnMemory();
		void Get();

	private:
		Type m_resources[size];
		// stack m_freeResources; 
	};

#pragma region CONSTRUCTOR

	template <class T, bool isStatic, typename SizeType, SizeType size>
	MemoryPool<T, isStatic, SizeType, size>::MemoryPool()
	{
	}

	template <class T, bool isStatic, typename SizeType, SizeType size>
	MemoryPool<T, isStatic, SizeType, size>::~MemoryPool()
	{
		delete[] m_resources;
	}

#pragma endregion CONSTRUCTOR
}

