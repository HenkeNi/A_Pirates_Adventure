#pragma once

namespace Hi_Engine
{
	class IService
	{
	public:
		virtual ~IService() = default;

		virtual void Shutdown() {};

		// Keep these??
		virtual void Deserialize(const char* path) {};
		virtual void Serialize() {};
	};
}