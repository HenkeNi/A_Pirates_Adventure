#pragma once

namespace Hi_Engine
{
	// Combine into single register function? if constexpr to check if component or system

	class ComponentRegistry;
	class SystemRegistry;

	class ECSRegistry
	{
	public:
		static ComponentRegistry& GetComponentRegistry();

		static SystemRegistry& GetSystemRegistry();


	
		// register serializer?

		// serialize entity

	private:
		//ComponentRegistry m_componentRegistry;
		//SystemRegistry m_systemRegistry;

		// event callbacks?

		// component serialization?
	};

#pragma region Templated_Methods


#pragma endregion
}