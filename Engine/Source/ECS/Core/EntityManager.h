#pragma once
#include "../Utility/ECSTypes.h"
#include "Utility/NonCopyable.h"
#include "../Utility/Entity.h"
#include <optional>
#include <queue>
#include <array>
#include "Utility/DataStructures/SparseSet.h"

namespace Hi_Engine
{
	class EntityManager : private NonCopyable
	{
	public:
		EntityManager();

		// TODO; make sure to increment version!

		void Initialize();
		std::optional<Entity> Create();

		bool Destroy(const Entity& entity);
		void DestroyAll(); // TODO: Check if work as expected

		std::vector<EntityID> GetEntities(Signature signature) const; // return entity or ids??

		// Get version?

		std::optional<Signature> GetSignature(EntityID id) const;
		void SetSignature(const Entity& entity, Signature signature);

		// TODO; Make sure to chekc version in is alive!
		bool IsValidEntity(const Entity& entity) const;
		bool IsAlive(const Entity& entity) const;
		
	private:
		//std::array<bool, MaxEntities> m_alive{ false };
		//std::array<uint8_t, MaxEntities> m_alive{ false };
		//std::bitset<MaxComponents> m_alive;

		// TODO; just id's? when creating, fetch version?


		// std::vector<Entity> m_active; // Or store entity as a whole??:::: set? std::unordered_set<Entity, EntityHash, EntityEqual> activeEntities; no need anymore??? use version(s)!?


		std::array<Signature, MaxEntities> m_signatures;
		std::array<uint32_t, MaxEntities> m_versions; // or entityVersions?

		SparseSet<Entity, EntityID> m_alive; // Use uint32_t as key? or ID as key?
		std::queue<EntityID> m_available; // sort?? priority queue or heap? rename AvailableIDs?
	};
}