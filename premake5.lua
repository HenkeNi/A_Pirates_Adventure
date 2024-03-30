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
		"%{prj.name}/",
		"%{prj.name}/Source/",
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

	files { "%{prj.name}/Source/**.h", "%{prj.name}/Source/**.hpp", "%{prj.name}/Source/**.cpp" }

	includedirs
	{
		"ThirdParty/GLEW/include",
		"ThirdParty/GLFW/include",
		"ThirdParty/FreeType/include",
		"ThirdParty/FastNoise/",
		"ThirdParty/glm",
		"Engine/Hi_Engine.h",
		"%{prj.name}/Source",
		"%{prj.name}/Source/AI",
		"%{prj.name}/Source/Commands",
		"%{prj.name}/Source/DataTypes",
		"%{prj.name}/Source/ECS",
		"%{prj.name}/Source/Gameplay",
		"%{prj.name}/Source/PostMaster",
		"%{prj.name}/Source/Precompiled",
		"%{prj.name}/Source/Registration",
		"%{prj.name}/Source/Scenes",
		"%{prj.name}/Source/Utility",
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
		"ThirdParty/FreeType/include",
		"ThirdParty/GLEW/include",
		"ThirdParty/GLFW/include/",
		"ThirdParty/glm",
		--"ThirdParty/rapidjson",
		--"ThirdParty/stb_image",
		"Engine/Source",
		"Game/Source",
		"%{prj.name}/Source/Precompiled"
	}

	-- (Linker/General -> Additional Library Directories)
	libdirs
	{
		"ThirdParty/FreeType/lib",
        "ThirdParty/GLEW/lib/Release/x64/",
        "ThirdParty/GLFW/lib-vc2022/",
		--"Bin/" .. outputdir .."/Game",
		--"Bin/" .. outputdir .."/Engine",
        --"ThirdParty/glm",
        --"ThirdParty/rapidjson",
        --"ThirdParty/stb_image",
	}

	-- (Linker/Input -> Additional Dependencies)
	links
	{
		"Engine",
		"Game",

		-- External libraries
		"opengl32.lib",
		"glew32s.lib",
		"glfw3.lib",
		"freetype.lib"
	}

	filter "system:windows"
		systemversion "latest"
	
	filter "configurations:Debug"
		defines "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "Release"
		optimize "on"
