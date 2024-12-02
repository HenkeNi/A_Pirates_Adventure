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

	document.AddMember("Scene", "MainMenu", allocator);

	rapidjson::Value components(rapidjson::kObjectType);

	for (auto& [type, componentArray] : m_componentArrays)
	{
		auto iterator = std::find_if(registry.begin(), registry.end(), [&](const auto& entry)
		{
			return entry.second.Type == type;
		});

		if (iterator != registry.end())
		{
			// std::function<void(const void*)> serialize = std::bind(iterator->second.SerializeComponent, std::placeholders::_1, component);
			//componentArray->ForEachComponent(serialize);


			rapidjson::Value compArray(rapidjson::kArrayType);
			
			// TODO; pass in corresponding entity as well...
			// components.AddMember(type, allocator);

			componentArray->ForEachComponent([&](Entity entity, const void* comp) // pass in entity as well??? or pass along index isntead? cant get both entity and index
			{
					iterator->second.SerializeComponent(comp, { entity,  compArray, allocator });
			});

			components.AddMember(rapidjson::Value(iterator->first.c_str(), allocator), compArray, allocator);


			//components.AddMember(iterator->first.c_str(), compArray, allocator);
			//auto serialization = [&](const void*) { iterator->second.SerializeComponent; }; // std::bind

			//componentArray->ForEachComponent(serialization); // pass in document as well? use for each cmoponent in systems?????
			//componentArray->ForEachComponent(iterator->second.SerializeComponent); // pass in document as well? use for each cmoponent in systems?????
		}
	}

	document.AddMember("components", components, allocator);

	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	document.Accept(writer);



	std::ofstream ofs("../Game/Assets/Saved/Scenes/MainMenu.json");
	ofs << buffer.GetString();
	ofs.close();
}

void ComponentManager::DeserializeComponents()
{

}