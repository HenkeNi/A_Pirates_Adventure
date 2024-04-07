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
	
	files { "%{prj.name}/Source/**.h", "%{prj.name}/Source/**.hpp", "%{prj.name}/Source/**.cpp" }

	-- Include directories are relative to root folder (solution directory)  (Creates a table)
	IncludeDir = {}
	IncludeDir["GLFW"]		 = "ThirdParty/GLFW/include"
	IncludeDir["GLEW"]		 = "ThirdParty/GLEW/include"
	IncludeDir["rapidjson"]  = "ThirdParty/rapidjson"
	IncludeDir["stb_image"]  = "ThirdParty/stb_image"
	IncludeDir["FreeType"]   = "ThirdParty/FreeType/include"
	IncludeDir["FastNoise"]  = "ThirdParty/FastNoise"
	IncludeDir["glm"]		 = "ThirdParty/glm"

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
		--"ThirdParty/FreeType/lib/"
        --"ThirdParty/glm",
        --"ThirdParty/rapidjson",
        --"ThirdParty/stb_image",
	}

	-- (Linker/Input -> Additional Dependencies)
	links
	{
		-- External libraries
		"glfw3_mt",
		"glew32s",
		"opengl32",
		"freetype",

		"gdi32",      -- For GLFW on Windows
	    "user32",     -- For GLFW on Windows
		"kernel32",   -- For GLFW on Windows
		"ole32"       -- For GLFW on Windows
	}

	filter "system:windows"
		systemversion "latest"
	
	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"
		libdirs { "ThirdParty/FreeType/lib/Debug" }

	filter "configurations:Release"
		runtime "Release"
		optimize "on"
		libdirs { "ThirdParty/FreeType/lib/Release" }


-- Game Project
project "Game"
	location "Game"
	kind "StaticLib"
	staticruntime "On"

	--targetname ("%{prj.name}")
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
	staticruntime "on"

	--targetname ("%{prj.name}")
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
		--"ThirdParty/GLFW/include/",
		"ThirdParty/glm",
		--"ThirdParty/rapidjson",
		--"ThirdParty/stb_image",
		"Engine/Source",
		"Game/Source",
		"%{prj.name}/Source/Precompiled"
	}

	--linkGLFW()

	--defines
	--{
	--	"GLEW_STATIC"
	--}
	-- (Linker/General -> Additional Library Directories)
		
	libdirs
	{
		--"ThirdParty/FreeType/lib",
        --"ThirdParty/GLEW/lib/Release/x64/",
        --"ThirdParty/GLFW/lib-vc2022/",
        --"ThirdParty/glm",
        --"ThirdParty/rapidjson",
        --"ThirdParty/stb_image",
	}

	links
	{
		"Engine",
		"Game"
	}

	filter "system:windows"
		systemversion "latest"
	
	filter "configurations:Debug"
		defines "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "Release"
		optimize "on"
