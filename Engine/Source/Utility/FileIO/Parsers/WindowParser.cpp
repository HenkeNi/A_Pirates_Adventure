#include "Pch.h"
#include "WindowParser.h"

namespace Hi_Engine
{
	WindowData WindowParser::Parse(rapidjson::Document& aDocument)
	{
		auto obj = aDocument["window"].GetObj();

		WindowData windowData;
		windowData.m_size		= { obj["size"]["width"].GetUint(), obj["size"]["height"].GetUint() };
		windowData.m_name		= obj["name"].GetString();
		windowData.m_iconPath	= obj["icon_path"].GetString();
 
		return windowData;
	}
}