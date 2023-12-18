#pragma once
#include "../Data/Structs.h"

namespace Hi_Engine	 
{
	class WindowParser 
	{
	public:
		WindowData Parse(rapidjson::Document& aDocument);
	};
}