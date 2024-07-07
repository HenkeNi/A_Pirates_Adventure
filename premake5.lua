-- Solution Details
workspace "A_Pirates_Adventure"
	configurations { "Debug", "Release" }
	architecture "x64"
	startproject "Launcher"
	language "C++"
	cppdialect "C++20"

    -- Output directories
	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"	


-- Engine Project
project "Engine"
	location "Engine"
	kind "StaticLib"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "Pch.h"
	pchsource "Engine/Source/Precompiled/Pch.cpp"
	
	files 
	{ 
		"%{prj.name}/Hi_Engine.h", 
		"%{prj.name}/Source/**.h", 
		"%{prj.name}/Source/**.hpp", 
		"%{prj.name}/Source/**.cpp",
		"%{prj.name}/Dependencies/**h",
		"%{prj.name}/Dependencies/**cpp"
	}

	-- Include directories are relative to root folder (solution directory)  (Creates a table)
	IncludeDir = {}
	IncludeDir["GLFW"]		 = "%{prj.name}/Dependencies/GLFW/include"
	IncludeDir["GLEW"]		 = "%{prj.name}/Dependencies/GLEW/include"
	IncludeDir["rapidjson"]  = "%{prj.name}/Dependencies/rapidjson"
	IncludeDir["stb_image"]  = "%{prj.name}/Dependencies/stb_image"
	IncludeDir["FreeType"]   = "%{prj.name}/Dependencies/FreeType/include"
	IncludeDir["FastNoise"]  = "%{prj.name}/Dependencies/FastNoise"
	IncludeDir["glm"]		 = "ThirdParty/glm"
	IncludeDir["irrKlang"]	 = "%{prj.name}/Dependencies/irrKlang/include"

	-- (C++/Preprocessor -> Preprocessor Definitions)
	defines { "GLEW_STATIC" }

	-- (C++/General -> Additional Include Directories)
	includedirs
	{
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLEW}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.FastNoise}",
		"%{IncludeDir.FreeType}",
		"%{IncludeDir.rapidjson}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.irrKlang}",
		"%{prj.name}/",
		"%{prj.name}/Dependencies/ImGui",
		"%{prj.name}/Dependencies/GLEW",
		"%{prj.name}/Source/",
		"%{prj.name}/Source/Core",
		"%{prj.name}/Source/Data",
		"%{prj.name}/Source/Precompiled",
		"%{prj.name}/Source/Utility"
	}
	
	libdirs
	{
        "%{prj.name}/Dependencies/GLFW/lib-vc2022/",
        "%{prj.name}/Dependencies/GLEW/lib/Release/x64/",
		"%{prj.name}/Dependencies/irrKlang/lib/"
	}

	-- (Linker/Input -> Additional Dependencies)
	links
	{
		"glfw3_mt",
		"glew32s",
		"opengl32",
		"freetype",
		"irrKlang"
	}

	filter "files:Engine/Dependencies/**.cpp"
		flags { "NoPCH" }

	filter "system:windows"
		systemversion "latest"
		links
		{
			"gdi32",
			"user32",
			"kernel32",
			"ole32"
		}

	filter "configurations:Debug"
        defines { "DEBUG" }
		symbols "on"
		runtime "Debug"
		libdirs 
		{ 
			"%{prj.name}/Dependencies/FreeType/lib/Debug", 
		}

	filter "configurations:Release"
        defines { "NDEBUG" }
		optimize "on"
		runtime "Release"
		libdirs 
		{ 
			"%{prj.name}/Dependencies/FreeType/lib/Release",
		}


-- Game Project
project "Game"
	location "Game"
	kind "StaticLib"
	staticruntime "On"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "Pch.h"
	pchsource "Game/Source/Precompiled/Pch.cpp"

	files { "%{prj.name}/Source/**.h", "%{prj.name}/Source/**.hpp", "%{prj.name}/Source/**.cpp" }

	includedirs
	{
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
        defines { "DEBUG" }
		symbols "on"
		runtime "Debug"

	filter "configurations:Release"
        defines { "NDEBUG" }
		optimize "on"
		runtime "Release"


-- Launcher Project
project "Launcher"
	location "Launcher"
	kind "ConsoleApp"
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
		"Engine/Source",
		"Game/Source",
		"%{prj.name}/Source/Precompiled"
	}
		
	links
	{
		"Engine",
		"Game"
	}

	postbuildcommands
	{
		"{COPY} ../Engine/Dependencies/irrKlang/lib/irrKlang.dll %{cfg.targetdir}",
		"{COPY} ../Engine/Dependencies/irrKlang/lib/ikpMP3.dll %{cfg.targetdir}"
	}

	filter "system:windows"
		systemversion "latest"
	
	filter "configurations:Debug"
        defines { "DEBUG" }
		symbols "on"

	filter "configurations:Release"
        defines { "NDEBUG" }
		optimize "on"