project "Game"
	location "Game"
	kind "StaticLib"
 	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "Pch.h"
	pchsource "Game/Source/Precompiled/Pch.cpp"

	files
	{
		"%{prj.name}/Source/**.h",
		"%{prj.name}/Source/**.cpp"
	}


	includedirs
	{
		"%{prj.name}/Source"
		"%{IncludeDir.glm}",
	}

	links
	{
		"Engine" -- needs to reference engien (but not other way around...)
	}

	filter "system:windows"
		systemversion "latest"
	
		defines
		{
			"GLEW_STATIC"
		}

	filter "configurations:Debug"
		defines "_DEBUG"
		symbols "on"

	filter "configurations:Release"
		defines "_RELEASE"
		optimize "on"

	filter "configurations:Dist"
		optimize "on"
