#pragma once
#include "../Utility/ECSTypes.h"

#include <optional>
#include <queue>

namespace Hi_Engine
{
	class EntityManager
	{
	public:
		void Initialize();
		std::optional<Entity> Create();

		void Destroy(Entity entity);
		void DestroyAll();

		inline const std::vector<Entity>& GetActiveEntities() const { return m_active; }

		std::vector<Entity> GetEntities(const Signature& signature) const;
		std::optional<Entity> GetEntity(const Signature& signature) const;

		std::optional<Signature> GetSignature(Entity entity) const;
		void SetSignature(Entity entity, const Signature& signature);

		bool IsValidEntity(Entity entity) const;

	private:
		std::vector<Entity> m_active;
		std::queue<Entity> m_available;

		std::array<Signature, MaxEntities> m_signatures;
	};
}