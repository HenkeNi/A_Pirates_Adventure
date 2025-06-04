#pragma once
//#include "Utility/ECSTypes.h"
///#include "Factory/EntityFactory.h"

namespace Hi_Engine
{
	// TODO; make into a service?
	// Regisresting; Combine into single register function? if constexpr to check if component or system

	class EntityFactory;

	class IComponentFactory;

	class ComponentRegistry;
	class SystemRegistry;

	// scene registry?

	// replace with (global) Registry class? (service?)
	//  
	class ECSRegistry
	{
	public:
		static ComponentRegistry& GetComponentRegistry();

		static SystemRegistry& GetSystemRegistry();

		[[nodiscard]] inline static EntityFactory& GetEntityFactory() { return *s_entityFactory; }

		// Handles all registring? Register Component takes care of both CompoentRegistry and Componet Serialization?

		// register serializer?

		// serialize entity

	private:
		///store uniqueptr insted??s
		static std::unique_ptr<EntityFactory> s_entityFactory; // Not static? Put factory here?? store
		//inline static EntityFactory m_entityFactory; // Not static? Put factory here?? store


		// inline static std::unordered_map<ComponentID, std::unique_ptr<IComponentFactory>> m_componentFactories;

		// Stores factories

		//ComponentRegistry m_componentRegistry;
		//SystemRegistry m_systemRegistry;

		// component serialization?

		// event callbacks?
		//inline static std::unordered_map<const char*, std::function<void(Entity)>> Callbacks; // Maybe in Timer/Button Component (or system), or separate Callback/Action component?
	};

#pragma region Templated_Methods


#pragma endregion
}