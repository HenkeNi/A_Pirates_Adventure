project "Engine"
	location "Engine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "Pch.h"
	pchsource "Engine/Source/Precompiled/Pch.cpp"
	
	files
	{
		"%{prj.name}/Source/**.h",
		"%{prj.name}/Source/**.cpp",
	}


	-- Include directories are relative to root folder (solution directory)  (Creates a table)
	IncludeDir = {}
	IncludeDir["FreeType"]  = "ThirdParty/FreeType/include"
	IncludeDir["rapidjson"] = "ThirdParty/rapidjson"
	IncludeDir["stb_image"] = "ThirdParty/stb_image"
	IncludeDir["GLEW"]		= "ThirdParty/GLEW/include"
	IncludeDir["GLFW"]		= "ThirdParty/GLFW/include"
	IncludeDir["glm"]		= "ThirdParty/glm"


-- group "Dependencies"
	-- include "ThirdParty/GLEW"
	-- include "ThirdParty/GLFW" 
-- group ""

	-- Equivalent to 'C/C++ -> Preprocessor -> Preprocessor Definitions
	defines
	{}


	-- Equivalent to 'C/C++ -> General -> Additional Include Directories'
	includedirs
	{
		"%{prj.name}/Source",
		"%{IncludeDir.FreeType}",
		"%{IncludeDir.GLEW}",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.rapidjson}",
		"%{IncludeDir.stb_image}"
	}

	-- Equivalent to 'Linker -> Input -> Additional Dependencies'
	links
	{
		"FreeType",
		"GLFW",
		"GLEW",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"
	
		defines
		{
			"GLEW_STATIC"
		}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		runtime "Release"
		optimize "on"