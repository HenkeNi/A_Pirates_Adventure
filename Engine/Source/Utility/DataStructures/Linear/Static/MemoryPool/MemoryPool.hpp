#pragma once
#include <cassert>
#include <cstddef>
#include <stack>
#include <vector>

// TODO: Make able to grow..
// TODO: Make able to add new resource??

namespace CommonUtilities
{
	template <class Type, bool isStatic = true, typename SizeType = unsigned, SizeType size = 48>
	class MemoryPool
	{
	public:
		~MemoryPool();
		
		MemoryPool(const MemoryPool&)						 = delete;
		MemoryPool& operator=(const MemoryPool&)			 = delete;

		static MemoryPool&	GetInstance();

		void				Init();
		Type*				GetResource();
		void				ReturnResource(Type* aResource);
		bool				IsEmpty()							const;

	private:
		MemoryPool();

		Type*				m_resources;
		std::stack<Type*>	m_freeResources;
	};

#pragma region CONSTRUCTOR

	template <class Type, bool isStatic, typename SizeType, SizeType size>
	MemoryPool<Type, isStatic, SizeType, size>::MemoryPool()
	{
	}

	template <class Type, bool isStatic, typename SizeType, SizeType size>
	MemoryPool<Type, isStatic, SizeType, size>::~MemoryPool()
	{
		delete[] m_resources;
	}

#pragma endregion CONSTRUCTOR

#pragma region Method_Definitions
	
	template <class Type, bool isStatic, typename SizeType, SizeType size>
	MemoryPool<Type, isStatic, SizeType, size>& MemoryPool<Type, isStatic, SizeType, size>::GetInstance()
	{
		static MemoryPool instance;
		return instance;
	}

	template <class Type, bool isStatic, typename SizeType, SizeType size>
	void MemoryPool<Type, isStatic, SizeType, size>::Init()
	{
		m_resources = new Type[size];
	}

	template <class Type, bool isStatic, typename SizeType, SizeType size>
	Type* MemoryPool<Type, isStatic, SizeType, size>::GetResource()
	{
		assert(!IsEmpty());

		auto* res = m_freeResources.top();
		m_freeResources.pop();

		return res;
	}

	template <class Type, bool isStatic, typename SizeType, SizeType size>
	void MemoryPool<Type, isStatic, SizeType, size>::ReturnResource(Type* aResource)
	{
		// TODO: "Clean" resource... (set to inactive if possible) call a clear function...

		m_freeResources.push(aResource);
	}

	template <class Type, bool isStatic, typename SizeType, SizeType size>
	bool MemoryPool<Type, isStatic, SizeType, size>::IsEmpty() const
	{
		return m_freeResources.empty();
	}

#pragma endregion Method_Definitions
}

