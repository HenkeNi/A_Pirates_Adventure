#pragma once

namespace Hi_Engine
{
	class IService
	{
	public:
		virtual ~IService() = default;
		virtual void Shutdown() {};
	};
}
