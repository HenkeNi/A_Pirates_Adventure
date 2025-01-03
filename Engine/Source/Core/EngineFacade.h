#pragma once
#include "../ECS/Utility/ECSTypes.h"
#include "../ECS/ECS.h"
// #include <rapidjson.h>
#include <optional>
#include <../../Dependencies/rapidjson/document.h> // dont expose to game?
//#include <document.h>


namespace Hi_Engine
{
	class Engine;
	class ECSCoordinator;

	// Rename: Engine utils?


	class EngineFacade
	{
	public:

		template <typename System, typename... Args>
		static void RegisterSystem(const char* name, Args&&... args);

		static std::optional<Entity> CreateEntityFromJson(const rapidjson::Value& jsonEntity);

	private:
		friend class Engine;

		static void Register(std::weak_ptr<ECSCoordinator> ecs);

		inline static std::weak_ptr<ECSCoordinator> s_ecs;
	};

	template<typename System, typename ...Args>
	inline void EngineFacade::RegisterSystem(const char* name, Args&& ...args)
	{
		if (auto ecs = s_ecs.lock())
		{
			//ecs->RegisterSystem(name, args);
			ecs->RegisterSystem<System, Args...>(name, std::forward<Args>(args)...);
			// ecs->RegisterSystem(name, args...);
		}
	}
}
