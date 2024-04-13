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
	
	files { "%{prj.name}/Hi_Engine.h", "%{prj.name}/Source/**.h", "%{prj.name}/Source/**.hpp", "%{prj.name}/Source/**.cpp" }

	-- Include directories are relative to root folder (solution directory)  (Creates a table)
	IncludeDir = {}
	IncludeDir["GLFW"]		 = "ThirdParty/GLFW/include"
	IncludeDir["GLEW"]		 = "ThirdParty/GLEW/include"
	IncludeDir["rapidjson"]  = "ThirdParty/rapidjson"
	IncludeDir["stb_image"]  = "ThirdParty/stb_image"
	IncludeDir["FreeType"]   = "ThirdParty/FreeType/include"
	IncludeDir["FastNoise"]  = "ThirdParty/FastNoise"
	IncludeDir["glm"]		 = "ThirdParty/glm"
	IncludeDir["irrKlang"]	 = "ThirdParty/irrKlang/include"

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
		"%{prj.name}/Source/",
		"%{prj.name}/Source/Core",
		"%{prj.name}/Source/Data",
		"%{prj.name}/Source/Precompiled",
		"%{prj.name}/Source/Utility"
	}
	
	libdirs
	{
        "ThirdParty/GLFW/lib-vc2022/",
        "ThirdParty/GLEW/lib/Release/x64/",
		"ThirdParty/irrKlang/lib/"
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
		runtime "Debug"
		symbols "on"
		libdirs 
		{ 
			"ThirdParty/FreeType/lib/Debug", 
		}

	filter "configurations:Release"
		runtime "Release"
		optimize "on"
		libdirs 
		{ 
			"ThirdParty/FreeType/lib/Release",
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
		"ThirdParty/FreeType/include",
		"ThirdParty/glm",
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
		"{COPY} ../ThirdParty/irrKlang/lib/irrKlang.dll %{cfg.targetdir}",
		"{COPY} ../ThirdParty/irrKlang/lib/ikpMP3.dll %{cfg.targetdir}"
	}

	filter "system:windows"
		systemversion "latest"
	
	filter "configurations:Debug"
		defines "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "Release"
		optimize "on"
