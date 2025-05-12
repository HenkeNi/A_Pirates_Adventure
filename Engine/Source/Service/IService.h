#pragma once

namespace Hi_Engine
{
	class IService
	{
	public:
		virtual ~IService() = default;

		virtual bool Initialize() { return true; }; // not pure virtual?
		virtual void Shutdown() {};

		// Keep these??
		virtual void Deserialize(/*const rapidjson::Value& json*/const char* path) {}; // accept a serializer instead?
		virtual void Serialize() {};
	};
}