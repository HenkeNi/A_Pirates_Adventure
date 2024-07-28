#pragma once

enum class eScene
{
	Game		/*= 1*/,
	Pause		/*= 2*/,
	Menu		/*= 4*/,
	Loading		/*= 8*/,
	Settings,
	Title		/*= 16*/,
	Overworld	/*= 32*/,
	Dungeon		/*= 64*/,
	Inventory,
	Count		/*= 128*/
	//GameOver, 
};
