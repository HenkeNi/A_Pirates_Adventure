#pragma once

namespace Hi_Engine
{
	class IService
	{
	public:
		~IService() = default;

		virtual void Initialize() = 0;
		virtual void Shutdown() = 0;
	};
}