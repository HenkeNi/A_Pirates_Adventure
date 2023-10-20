project "Launcher"
	location "Launcher"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "Pch.h"
	pchsource "Launcher/Source/Precompiled/Pch.cpp"

	files
	{
		"%{prj.name}/Source/**.h",
		"%{prj.name}/Source/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/ThirdParty/FreeType/include"
		"%{prj.name}/ThirdParty/GLEW/include"
		"%{prj.name}/ThirdParty/GLFW/include"
		"%{prj.name}/ThirdParty/glm"
		"%{prj.name}/ThirdParty/rapidjson"
		"%{prj.name}/ThirdParty/stb_image"
		"Engine/Source"
	}

	links
	{
		Engine,
		Game
	}

	filter "system:windows"
		systemversion "latest"
	
	filter "configurations:Debug"
		defines "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "Release"
		optimize "on"