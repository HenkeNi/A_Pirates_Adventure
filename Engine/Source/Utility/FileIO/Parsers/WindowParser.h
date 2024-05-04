#pragma once
#include "../Data/Structs.h"

// Todo; remove??
namespace Hi_Engine	 
{
	class WindowParser 
	{
	public:
		WindowData Parse(rapidjson::Document& aDocument);
	};
}