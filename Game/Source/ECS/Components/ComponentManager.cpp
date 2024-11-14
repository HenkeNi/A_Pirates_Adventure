#include "Pch.h"
#include "ComponentManager.h"

#include "ComponentIO.h"

#include <../Dependencies/rapidjson/stringbuffer.h> // FIX! Temp..
#include <../Dependencies/rapidjson/writer.h> // FIX! Temp..


ComponentManager::ComponentManager()
	: m_nextComponentType{ 1 }
{
}

void ComponentManager::RemoveAllComponents(Entity entity)
{
	for (auto& [type, componentArray] : m_componentArrays)
	{
		componentArray->RemoveComponent(entity);
		/*if (void* removed = componentArray->RemoveComponent(entity))
		{
			auto itr = m_componentPools.find(type);
			if (itr != m_componentPools.end())
			{
				itr->second->ReturnResource(removed);
			}
		}*/
	}
}

void ComponentManager::SerializeComponents(ComponentRegistry& registry)
{
	// do in engine??
	rapidjson::Document document;
	document.SetObject();

	auto& allocator = document.GetAllocator();

	// store components in a map instead?

	for (auto& [type, componentArray] : m_componentArrays)
	{

		// componentArray->ForEachComponent(ComponentIO::Serialize);

		auto iterator = std::find_if(registry.begin(), registry.end(), [&](const auto& entry)
			{
				//return entry.second.Type == type;
				return true;
			});

		if (iterator != registry.end())
		{
			componentArray->ForEachComponent(iterator->second.SerializeComponent);

			
			//std::function<void(void*)> fnc = ComponentIO::Serialize;

			// How to get all components?? since need to cast to proper component array...

			//componentArray->ForEachComponent(iterator->second.SerializeComponent);

			// iterator->second.SerializeComponent(0);
		}
	}

	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	document.Accept(writer);

	std::ofstream ofs("../Game/Assets/Saved/Scenes/MainMenu.json");
	ofs << buffer.GetString();
	ofs.close();
}
