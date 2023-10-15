#pragma once
#include "../Base/ComponentBase.h"

struct ButtonComponent : public ComponentBase
{
	class Command* Command; // ??
};

// CYRRENTLY IN RENDEIRNG COMPONENTS?!
//struct TextComponent : public ComponentBase
//{
//	class Hi_Engine::Font&	Font;
//	CU::Vector4<float>		Color;
//	std::string				Text;
//	unsigned				Size = 32;
//};