workspace "Number"
    architecture "x64"
    startproject "Sandbox"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solutuon directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Number/vendor/GLFW/include"
IncludeDir["Glad"] = "Number/vendor/Glad/include"
IncludeDir["ImGui"] = "Number/vendor/ImGui"

include "Number/vendor/GLFW"
include "Number/vendor/Glad"
include "Number/vendor/ImGui"

project "Number"
    location "Number"
    kind "SharedLib"
    language "C++"
    staticruntime "off"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "numpch.h"
    pchsource "Number/src/numpch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "%{prj.name}/vendor/spdlog/include",
        "%{prj.name}/src",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}"
    }

    links
    {
        "GLFW",
        "Glad",
        "ImGui",
        "opengl32.lib",
        "dwmapi.lib"
    }

    filter "system:windows"
        cppdialect "C++20"
        systemversion "latest"

        defines
        {
            "NUM_PLATFORM_WINDOWS",
            "NUM_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }

        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
        }

    filter "configurations:Debug"
        defines "NUM_DEBUG"
        runtime "Debug"
        symbols "On"
        
    filter "configurations:Release"
        defines "NUM_RELEASE"
        runtime "Release"
        optimize "On"
    
    filter "configurations:Dist"
        defines "NUM_DIST"
        runtime "Release"
        optimize "On"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "Number/vendor/spdlog/include",
        "Number/src"
    }

    links
    {
        "Number"
    }

    filter "system:windows"
        cppdialect "C++20"
        systemversion "latest"

        defines
        {
            "NUM_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "NUM_DEBUG"
        runtime "Debug"
        symbols "On"
        
    filter "configurations:Release"
        defines "NUM_RELEASE"
        runtime "Release"
        optimize "On"

    filter "configurations:Dist"
        defines "NUM_DIST"
        runtime "Release"
        optimize "On"