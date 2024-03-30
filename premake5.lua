-- Solution Details
workspace "A_Pirates_Adventure"
	configurations { "Debug", "Release" }
	architecture "x64"
	startproject "Launcher"

    -- Set output directories for binaries
	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
	
-- Engine Project
project "Engine"
	location "Engine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	targetname ("%{prj.name}")
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "Pch.h"
	pchsource "Engine/Source/Precompiled/Pch.cpp"
	
	files { "%{prj.name}/Source/**.h", "%{prj.name}/Source/**.hpp", "%{prj.name}/Source/**.cpp" }

	-- Include directories are relative to root folder (solution directory)  (Creates a table)
	IncludeDir = {}
	IncludeDir["FastNoise"]  = "ThirdParty/FastNoise"
	IncludeDir["FreeType"]   = "ThirdParty/FreeType/include"
	IncludeDir["rapidjson"]  = "ThirdParty/rapidjson"
	IncludeDir["stb_image"]  = "ThirdParty/stb_image"
	IncludeDir["GLEW"]		 = "ThirdParty/GLEW/include"
	IncludeDir["GLFW"]		 = "ThirdParty/GLFW/include"
	IncludeDir["glm"]		 = "ThirdParty/glm"

	-- group "Dependencies"
	-- include "ThirdParty/GLEW"
	-- include "ThirdParty/GLFW" 
	-- group ""

	-- (C++/Preprocessor -> Preprocessor Definitions)
	defines
	{
		"GLEW_STATIC"
	}

	-- (C++/General -> Additional Include Directories)
	includedirs
	{
		"%{prj.name}/Source",
		"%{prj.name}/Source/Core",
		"%{prj.name}/Source/Data",
		"%{prj.name}/Source/Precompiled",
		"%{prj.name}/Source/Utility",
		"%{IncludeDir.FastNoise}",
		"%{IncludeDir.FreeType}",
		"%{IncludeDir.GLEW}",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.rapidjson}",
		"%{IncludeDir.stb_image}"
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


-- Game Project
project "Game"
	location "Game"
	kind "StaticLib"
 	language "C++"
	cppdialect "C++20"
	staticruntime "On"

	targetname ("%{prj.name}")
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
		"%{prj.name}/Source",
		 "%{prj.name}/../Engine/Hi_Engine.h",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Engine"
	}

	filter "system:windows"
		systemversion "latest"
	
	filter "configurations:Debug"
		defines "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "Release"
		optimize "on"


-- Launcher Project
project "Launcher"
	location "Launcher"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	targetname ("%{prj.name}")
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
		"%{prj.name}/ThirdParty/FreeType/include",
		"%{prj.name}/ThirdParty/GLEW/include",
		"%{prj.name}/ThirdParty/GLFW/include",
		"%{prj.name}/ThirdParty/glm",
		"%{prj.name}/ThirdParty/rapidjson",
		"%{prj.name}/ThirdParty/stb_image",
		"Engine/Source"
	}

	-- (Linker/Input -> Additional Dependencies)
	links
	{
		"Engine",
		"Game",

		-- External libraries
		"freetype",
		"opengl32",
		"glew32s",
		"glfw3"
	}

	filter "system:windows"
		systemversion "latest"
	
	filter "configurations:Debug"
		defines "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "Release"
		optimize "on"