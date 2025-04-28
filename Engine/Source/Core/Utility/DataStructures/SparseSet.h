#pragma once
#include "Utility/TypeTraits.h"

namespace Hi_Engine
{
	// Consider; 
	// * renaming to 'sparse_set'
	// * change to raw memory (KeyType* m_sparse, or std::unique_ptr<KeyType[]>
	// * use custom iterator
	
	template <typename ValueType, Integral KeyType = std::size_t>
	class SparseSet final
	{
	public:
		// ==================== Core API ====================
		// Construction/Destruction
		SparseSet(std::size_t initialSize = 1024);
		~SparseSet() = default;

		SparseSet(const SparseSet&) = default;
		SparseSet(SparseSet&&) noexcept = default;

		SparseSet& operator=(const SparseSet&) = default;
		SparseSet& operator=(SparseSet&&) noexcept = default;

		// ==================== Element Access ====================
		// Safe access (checked)
		const ValueType& At(KeyType key) const;
		ValueType& At(KeyType key);

		// Unsafe access (unchecked)
		const ValueType& operator[](KeyType key) const;
		ValueType& operator[](KeyType key);

		// Pointer access
		const ValueType* Get(KeyType key) const;
		ValueType* Get(KeyType key);

		// ==================== Modifiers ====================
		// Insertion
		template <typename... Args>	
		bool Emplace(KeyType key, Args&&... args);
		void Insert(KeyType key, ValueType&& value);

		// Removal
		bool Remove(KeyType key);
		void Clear();

		// Memory management
		void Reserve(std::size_t capacity);
		void ShrinkToFit();
		void Swap(SparseSet& other) noexcept;

		// ==================== Capacity ====================
		bool IsEmpty() const noexcept;
		std::size_t	Size() const;
		bool Contains(KeyType key) const;
		
		// ==================== Iterators ====================
		auto begin() { return m_dense.begin(); }
		auto end() { return m_dense.end(); }

		auto begin() const { return m_dense.begin(); }
		auto end() const { return m_dense.end(); }

		auto rbegin() { return m_dense.rbegin(); }
		auto rend() { return m_dense.rend(); }

		auto rbegin() const { return m_dense.rbegin(); }
		auto rend() const { return m_dense.rend(); }

	private:
		// ==================== Data Members ====================
		inline static constexpr KeyType InvalidIndex = std::numeric_limits<KeyType>::max();
		
		std::vector<KeyType> m_sparse;			// [Key] -> Index in m_dense (InvalidIndex = empty)
		std::vector<std::size_t> m_reverse;		// [Index in m_dense] -> Key
		std::vector<ValueType> m_dense;			// Contiguous active elements
	};

#pragma region Templated_Methods

	template <typename ValueType, Integral KeyType>
	SparseSet<ValueType, KeyType>::SparseSet(std::size_t initialSize)
	{
		m_sparse.resize(initialSize, InvalidIndex);
		m_reverse.resize(initialSize, InvalidIndex);

		m_dense.reserve(initialSize);
	}

	template<typename ValueType, Integral KeyType>
	inline const ValueType& SparseSet<ValueType, KeyType>::At(KeyType key) const
	{
		if (!Contains(key)) throw std::out_of_range("Invalid key");
		return m_dense[m_sparse[key]];
	}

	template<typename ValueType, Integral KeyType>
	inline ValueType& SparseSet<ValueType, KeyType>::At(KeyType key)
	{
		return const_cast<ValueType&>(std::as_const(*this).At(key));
	}

	template<typename ValueType, Integral KeyType>
	inline const ValueType& SparseSet<ValueType, KeyType>::operator[](KeyType key) const
	{
		assert(Contains(key));
		return m_dense[m_sparse[key]];
	}

	template<typename ValueType, Integral KeyType>
	inline ValueType& SparseSet<ValueType, KeyType>::operator[](KeyType key)
	{
		assert(Contains(key));
		return m_dense[m_sparse[key]];
	}

	template <typename ValueType, Integral KeyType>
	const ValueType* SparseSet<ValueType, KeyType>::Get(KeyType key) const
	{
		return Contains(key) ? &m_dense[m_sparse[key]] : nullptr;
	}

	template <typename ValueType, Integral KeyType>
	ValueType* SparseSet<ValueType, KeyType>::Get(KeyType key)
	{
		return Contains(key) ? &m_dense[m_sparse[key]] : nullptr;
	}

	template<typename ValueType, Integral KeyType>
	template<typename... Args>
	bool SparseSet<ValueType, KeyType>::Emplace(KeyType key, Args&&... args)
	{
		// Early exit for invalid key
		if (key < 0 || key == InvalidIndex)
		{
			return false;
		}

		// Key already exists: overwrite existing value
		if (Contains(key))
		{
			m_dense[m_sparse[key]] = ValueType(std::forward<Args>(args)...);
			return true;
		}

		// Resize sparse/reverse vectors if necessary
		if (static_cast<std::size_t>(key) >= m_sparse.size())
		{
			const std::size_t newSize = std::max(static_cast<std::size_t>(key) + 1, m_sparse.size() * 2);

			m_sparse.resize(newSize, InvalidIndex);			
			m_reverse.resize(newSize);
		}

		const KeyType index = static_cast<KeyType>(m_dense.size());

		m_sparse[key] = index;
		m_reverse[index] = key;

		m_dense.emplace_back(std::forward<Args>(args)...);
		return true;
	}

	template<typename ValueType, Integral KeyType>
	void SparseSet<ValueType, KeyType>::Insert(KeyType key, ValueType&& value)
	{
		Emplace(key, std::forward<ValueType>(value));
	}

	template <typename ValueType, Integral KeyType>
	bool SparseSet<ValueType, KeyType>::Remove(KeyType key)
	{
		if (!Contains(key))
			return false;

		const KeyType indexToRemove = m_sparse[key];
		const std::size_t lastIndex = m_dense.size() - 1;

		if (indexToRemove != static_cast<KeyType>(lastIndex))
		{
			m_dense[indexToRemove] = std::move(m_dense[lastIndex]);

			// Update the moved element's sparse index
			const KeyType lastKey = m_reverse[lastIndex];
			m_sparse[lastKey] = indexToRemove;
			m_reverse[indexToRemove] = lastKey;
		}

		m_sparse[key] = InvalidIndex;
		m_dense.pop_back();

		return true;
	}

	template <typename ValueType, Integral KeyType>
	void SparseSet<ValueType, KeyType>::Clear()
	{
		m_dense.clear();
		std::fill(m_sparse.begin(), m_sparse.end(), InvalidIndex);
		std::fill(m_reverse.begin(), m_reverse.end(), InvalidIndex);
	}

	template<typename ValueType, Integral KeyType>
	inline void SparseSet<ValueType, KeyType>::Reserve(std::size_t capacity)
	{
		m_sparse.reserve(capacity);
		m_reverse.reserve(capacity);
		m_dense.reserve(capacity);
	}

	template<typename ValueType, Integral KeyType>
	inline void SparseSet<ValueType, KeyType>::ShrinkToFit()
	{
		m_sparse.shrink_to_fit();
		m_reverse.shrink_to_fit();
		m_dense.shrink_to_fit();
	}

	template<typename ValueType, Integral KeyType>
	inline void SparseSet<ValueType, KeyType>::Swap(SparseSet& other) noexcept
	{
		m_sparse.swap(other.m_sparse);
		m_reverse.swap(other.m_reverse);
		m_dense.swap(other.m_dense);
	}

	template<typename ValueType, Integral KeyType>
	inline bool SparseSet<ValueType, KeyType>::IsEmpty() const noexcept
	{
		return m_dense.empty();
	}

	template <typename ValueType, Integral KeyType>
	std::size_t SparseSet<ValueType, KeyType>::Size() const
	{
		return m_dense.size();
	}

	template <typename ValueType, Integral KeyType>
	bool SparseSet<ValueType, KeyType>::Contains(KeyType key) const
	{
		return key >= 0 && static_cast<std::size_t>(key) < m_sparse.size() && m_sparse[key] != InvalidIndex;
	}

#pragma endregion Templated_Methods
}