#include "Pch.h"
#include "WindowParser.h"

namespace Hi_Engine
{
	WindowData WindowParser::Parse(rapidjson::Document& aDocument)
	{
		auto obj = aDocument["window"].GetObj();

		WindowData windowData;
		windowData.Size		= { obj["size"]["width"].GetUint(), obj["size"]["height"].GetUint() };
		windowData.Identifier		= obj["name"].GetString();
		windowData.IconPath	= obj["icon_path"].GetString();
 
		return windowData;
	}
}