#pragma once
#include <cassert>
#include <cstddef>
#include <stack>
#include <vector>


// Vector of shared_ptrs instead? => return a weak_ptr??
// TODO: Make able to grow..?	Make able to add new resource??
// Check Allocators (Cherno)
// Rename; ObjectPool?

namespace CommonUtilities
{
	template <class Type, typename SizeType = unsigned, SizeType size = 1024>	// TODO; rmove parameters??
	class MemoryPool
	{
	public:
		~MemoryPool();
		
		MemoryPool(const MemoryPool&)						 = delete;
		MemoryPool& operator=(const MemoryPool&)			 = delete;

		static MemoryPool&	GetInstance(); 	

		Type*				GetResource();
		void				ReturnResource(Type* aResource);				// Or have MemoryPOol check each frame if cmopoennt is destyoed (takes in back)... less optimized...		OR Listens for destoyed event... then takes all compoennts??
		bool				IsEmpty()							const;

	private:
		MemoryPool(); 

		Type*				m_resources;			// vector of type instead??
		std::stack<Type*>	m_availableResources;	// Counter instead??		Sort?? so in sequence in memory?? 
	};

#pragma region CONSTRUCTOR

	template <class Type, typename SizeType, SizeType size>
	MemoryPool<Type, SizeType, size>::MemoryPool()
		: m_resources{ new Type[size] }
	{
		for (int i = 0; i < size; ++i)
		{
			//auto f = m_resources[i];
			m_availableResources.push(&m_resources[i]);
		}
	}

	template <class Type, typename SizeType, SizeType size>
	MemoryPool<Type, SizeType, size>::~MemoryPool()
	{
		delete[] m_resources;
	}

#pragma endregion CONSTRUCTOR

#pragma region Method_Definitions
	
	template <class Type, typename SizeType, SizeType size>
	MemoryPool<Type, SizeType, size>& MemoryPool<Type, SizeType, size>::GetInstance()
	{
		static MemoryPool instance;
		return instance;
	}

	template <class Type, typename SizeType, SizeType size>
	Type* MemoryPool<Type, SizeType, size>::GetResource()
	{
		assert(!IsEmpty());

		auto* res = m_availableResources.top();
		m_availableResources.pop();

		return res;
	}

	template <class Type, typename SizeType, SizeType size>
	void MemoryPool<Type, SizeType, size>::ReturnResource(Type* aResource)
	{
		// TODO: "Clean" resource... (set to inactive if possible) call a clear function...
		m_availableResources.push(aResource);
	}

	template <class Type, typename SizeType, SizeType size>
	bool MemoryPool<Type, SizeType, size>::IsEmpty() const
	{
		return m_availableResources.empty();
	}

#pragma endregion Method_Definitions
}

