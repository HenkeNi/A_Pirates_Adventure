#pragma once
#include "ECSTypes.h"


class EntityManager
{
public:
	EntityManager();

	Entity Create();

	void Destroy(Entity entity);
	void DestroyAll();

	inline const std::vector<Entity>& GetActiveEntities() const { return m_active; }

	std::vector<Entity> GetEntities(const Signature& signature) const;
	std::optional<Entity> GetEntity(const Signature& signature) const;

	void SetSignature(Entity entity, const Signature& signature);
	Signature GetSignature(Entity entity) const;

private:
	std::queue<Entity> m_available;
	std::vector<Entity> m_active;

	std::array<Signature, MaxEntities> m_signatures;
};