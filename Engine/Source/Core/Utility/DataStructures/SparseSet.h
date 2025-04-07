#pragma once

namespace Hi_Engine
{
	//class SparseSetIterator
	//{};

	// rename sparse_set?

	template <typename ValueType, typename KeyType = std::size_t>
	class SparseSet
	{
	public:
		SparseSet(std::size_t initialSize = 1024); // template argument instead?

		template <typename... Args>	
		bool Add(KeyType key, Args&&... args); // insert? instaed emplace?

		//void Insert();

		bool Remove(KeyType key);
		bool Contains(KeyType key) const;

		const std::vector<ValueType>& Data() const;
		std::vector<ValueType>& Data();

		const ValueType* Get(KeyType key) const; // optional instead? maybe bool (safeFlag) templte argument?
		ValueType* Get(KeyType key);

		std::size_t	Size() const;
		void Clear();

		std::size_t Search(KeyType key)
		{
			return -1;
		}

	private:
		inline static constexpr std::size_t InvalidIndex = std::numeric_limits<KeyType>::max();

		//std::array<KeyType, size> m_sparse; // stores indexes of actual elements
		// std::array<std::size_t, size> m_reverse;

		// use array instead? (instead of key type, always store std::size-t?
		std::vector<KeyType> m_sparse; // stores indexes of actual elements
		std::vector<std::size_t> m_reverse; // right type? or use unorded map for this one?

		std::vector<ValueType> m_elements; // Stores elements densly packed.. m_dense
	};

#pragma region Templated_Methods

	template <typename ValueType, typename KeyType>
	inline SparseSet<ValueType, KeyType>::SparseSet(std::size_t initialSize)
		// : m_allocatingSize{ }
	{
		m_sparse.resize(initialSize, InvalidIndex);
		m_reverse.resize(initialSize, InvalidIndex);

		m_elements.reserve(initialSize);
	}

	template<typename ValueType, typename KeyType>
	template<typename ...Args>
	inline bool SparseSet<ValueType, KeyType>::Add(KeyType key, Args&& ...args)
	{
		// If key already exists, return false early
		if (key < m_sparse.size() && m_sparse[key] != InvalidIndex)
		{
			// Maybe update component?
			// m_elements[m_sparse[key]] = std::forward<Args>(args)...;
			return false;
		}

		// Expand vector (sparse) if key is out of bounds
		if (key >= m_sparse.size())
		{
			std::size_t newSize = std::max(key + 1, m_sparse.size() * 2);
			m_sparse.resize(newSize, InvalidIndex);
			
			// resize reverse as well?
			m_reverse.resize(newSize);
		}

		auto index = static_cast<KeyType>(m_elements.size());

		m_sparse[key] = index;
		m_reverse[index] = key;

		m_elements.emplace_back(std::forward<Args>(args)...);

		return true;
	}

	template <typename ValueType, typename KeyType>
	inline bool SparseSet<ValueType, KeyType>::Remove(KeyType key)
	{
		if (!Contains(key))
			return false;

		auto indexToRemove = m_sparse[key];
		std::size_t lastIndex = m_elements.size() - 1;

		if (indexToRemove != lastIndex) // is it better not to check, and instead always swap? check performance
		{
			m_elements[indexToRemove] = std::move(m_elements[lastIndex]);

			// Update the moved keys index..
			auto keyToMove = m_reverse[lastIndex];

			m_sparse[keyToMove] = indexToRemove;
			m_reverse[indexToRemove] = keyToMove;

			//  std::swap(dense[indexToRemove], dense[lastIndex]);
			// std::swap(indices[indexToRemove], indices[lastIndex]);
			// reverse[entityIdOfLast] = indexToRemove; // Update reverse mapping
		}

		m_sparse[key] = InvalidIndex; 
		m_reverse[lastIndex] = InvalidIndex;

		m_elements.pop_back();

		return true;
	}

	template <typename ValueType, typename KeyType>
	inline bool SparseSet<ValueType, KeyType>::Contains(KeyType key) const
	{
		return key < m_sparse.size() && m_sparse[key] != InvalidIndex; // Correct?
	}

	template <typename ValueType, typename KeyType>
	inline const std::vector<ValueType>& SparseSet<ValueType, KeyType>::Data() const
	{
		return m_elements;
	}

	template <typename ValueType, typename KeyType>
	inline std::vector<ValueType>& SparseSet<ValueType, KeyType>::Data()
	{
		return m_elements;
	}

	template <typename ValueType, typename KeyType>
	inline const ValueType* SparseSet<ValueType, KeyType>::Get(KeyType key) const
	{
		return Contains(key) ? &m_elements[m_sparse[key]] : nullptr;
	}

	template <typename ValueType, typename KeyType>
	inline ValueType* SparseSet<ValueType, KeyType>::Get(KeyType key)
	{
		return Contains(key) ? &m_elements[m_sparse[key]] : nullptr;
	}

	template <typename ValueType, typename KeyType>
	inline std::size_t SparseSet<ValueType, KeyType>::Size() const
	{
		return m_elements.size();
	}

	template <typename ValueType, typename KeyType>
	inline void SparseSet<ValueType, KeyType>::Clear()
	{
		m_elements.clear();
		std::fill(m_sparse.begin(), m_sparse.end(), InvalidIndex);
	}

#pragma endregion Templated_Methods
}