#pragma once
#include "../ECS/Utility/ECSTypes.h"
//#include "../Utility/EntityHandle.h"

namespace Hi_Engine
{
	class PrefabRegistry;
	class World;
	class EntityHandle;

	class EntityFactory
	{
	public:
		//EntityFactory();

		// Find another way!, dont expose as public, should only be called once..
		void Initialize(std::weak_ptr<const PrefabRegistry> registry);

		std::optional<EntityHandle> CreateFromPrefab(World& world, const std::string& name); // bool notify = true

	private:
		std::weak_ptr<const PrefabRegistry> m_prefabRegistry;
		// Component registry??
	};


	// std::function<void(Entity)> AddComponent;
	// std::function<void(Entity, const ComponentProperties&)> InitializeComponent;
}