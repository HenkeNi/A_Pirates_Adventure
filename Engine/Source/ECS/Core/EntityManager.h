#pragma once
#include "Utility/NonCopyable.h"
#include "Utility/DataStructures/SparseSet.h"
#include "../Utility/Entity.h"
#include "../Utility/ECSTypes.h"
#include <optional>
#include <queue>
#include <array>

namespace Hi_Engine
{
	// Consider; replacing Queue with a priority queue or heap (make sure lower ids get used first). rename AvailableIDs?

	class EntityManager : private NonCopyable
	{
	public:
		// ==================== Construction/Destruction ====================
		EntityManager();
		~EntityManager() = default;

		EntityManager(EntityManager&&) = default;
		EntityManager& operator=(EntityManager&&) = default;

		// ==================== Lifecycle ====================
		[[nodiscard]] std::optional<Entity> Create() noexcept; // safe to use noexcept?
		bool Destroy(const Entity& entity) noexcept;
		void DestroyAll() noexcept;

		// ==================== Queries ====================
		[[nodiscard]] bool IsValidEntity(const Entity& entity) const noexcept;
		[[nodiscard]] bool IsAlive(const Entity& entity) const noexcept;

		// ==================== Signature Management ====================
		[[nodiscard]] std::optional<Signature> GetSignature(EntityID id) const noexcept;
		void SetSignature(const Entity& entity, Signature signature);

		// ==================== Bulk Operations ====================
		[[nodiscard]] std::vector<Entity> GetEntities(Signature signature) const;
		[[nodiscard]] std::vector<EntityID> GetEntityIDs(Signature signature) const;

		// ==================== Statistics ====================
		[[nodiscard]] inline std::size_t GetAliveCount() const noexcept { return m_alive.Size(); }
		[[nodiscard]] inline std::size_t GetAvailableCount() const noexcept { return m_available.size(); }
		
	private:
		// ==================== Helpers ====================
		void InitializeEntityIDs() noexcept;

		// ==================== Data Members ====================
		std::array<Signature, MaxEntities> m_signatures;
		std::array<uint32_t, MaxEntities> m_versions;

		SparseSet<Entity, EntityID> m_alive;
		std::queue<EntityID> m_available;
	};
}