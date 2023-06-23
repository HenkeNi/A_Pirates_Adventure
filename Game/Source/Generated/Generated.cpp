#include "Pch.h"
#include "Generated.h"
//#include "ObjectManager.h"
#include "../Builders/ComponentBuilder.hpp"

// Todo; Put in #include file?
#include "../GameObject/Components/Rendering/Sprite/C_Sprite.h"
#include "../GameObject/Components/Core/Transform/C_Transform.h"


namespace Generated
{
	void RegisterComponents()
	{
		//ObjectManager::RegisterBuilder("sprite",		new ConcreteComponentBuilder<C_Sprite>{});
		//ObjectManager::RegisterBuilder("transform",		new ConcreteComponentBuilder<C_Transform>{});
	}

	void RegisterPrototypes()
	{
		//ObjectManager::LoadPrototypes("../Bin/Assets/Json/Prototypes/Prototypes_Enemy.json");
		//ObjectManager::LoadPrototypes("../Bin/Assets/Json/Prototypes/Prototypes_Environment.json");
		//ObjectManager::LoadPrototypes("../Bin/Assets/Json/Prototypes/Prototypes_UI.json");
	}

	void RegisterScenes()
	{
		// maybe??
	}
}
