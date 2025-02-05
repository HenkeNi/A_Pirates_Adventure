#include "Pch.h"
#include "EngineFacade.h"
#include "ECS/ECS.h"

namespace Hi_Engine
{
	void EngineFacade::Register(std::weak_ptr<ECSCoordinator> ecs)
	{
		s_ecs = ecs;
	}
	
	std::optional<Entity> EngineFacade::CreateEntityFromJson(const rapidjson::Value& jsonEntity)
	{
		return s_ecs.lock()->CreateEntityFromJson(jsonEntity);
	}

	std::optional<Entity> EngineFacade::CreateEntityFromPrefab(const char* type)
	{
		return s_ecs.lock()->CreateEntityFromPrefab(type);
	}
}

