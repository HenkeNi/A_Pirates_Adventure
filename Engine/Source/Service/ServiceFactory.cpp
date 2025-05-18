#include "Pch.h"
#include "ServiceFactory.h"

namespace Hi_Engine
{
	ServiceFactory& ServiceFactory::GetInstance()
	{
		static ServiceFactory instance;
		return instance;
	}
}
