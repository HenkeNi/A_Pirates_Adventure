project "Game"
	location "Game"
	kind "StaticLib"
 	language "C++"
	cppdialect "C++20"
	staticruntime "On"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "Pch.h"
	pchsource "Game/Source/Precompiled/Pch.cpp"

	files
	{
		"%{prj.name}/Source/**.h",
		"%{prj.name}/Source/**.hpp",
		"%{prj.name}/Source/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/Source"
		"%{IncludeDir.glm}",
	}

	links
	{
		"Engine"
	}

	filter "system:windows"
		systemversion "latest"
	
		defines
		{
			"GLEW_STATIC"
		}

	filter "configurations:Debug"
		defines "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "Release"
		optimize "on"
