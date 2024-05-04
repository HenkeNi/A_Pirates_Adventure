#include "Pch.h"
#include "WindowParser.h"

namespace Hi_Engine
{
	WindowData WindowParser::Parse(rapidjson::Document& aDocument)
	{
		auto obj = aDocument["window"].GetObj();

		WindowData windowData;
		windowData.Size		= { obj["size"]["width"].GetInt(), obj["size"]["height"].GetInt() };
		windowData.WindowName		= obj["name"].GetString();
		windowData.IconPath	= obj["icon_path"].GetString();
 
		return windowData;
	}
}