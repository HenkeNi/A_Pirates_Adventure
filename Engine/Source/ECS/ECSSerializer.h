#pragma once
#include "../Services/IService.h"
#include "Utility/ECSTypes.h"

namespace Hi_Engine
{
	// Or make static?

	class ECSSerializer : public IService
	{
	public:
		void SerializeEntity(EntityID id);
		
		//void DeserializeEntity();

		// register serialization

		template <typename T>
		void SerializeComponent(T&& component)
		{
			if constexpr (std::is_trivially_constructible_v<T>)
			{
				// Dump data...
			}
			else
			{
				// require serialize function...
			}
		}


	private:
	};
}