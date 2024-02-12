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
IncludeDir["glm"] = "Number/vendor/glm"

include "Number/vendor/GLFW"
include "Number/vendor/Glad"
include "Number/vendor/ImGui"

project "Number"
    location "Number"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "numpch.h"
    pchsource "Number/src/numpch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/vendor/glm/glm/**.hpp",
        "%{prj.name}/vendor/glm/glm/**.inl"
    }

    includedirs
    {
        "%{prj.name}/vendor/spdlog/include",
        "%{prj.name}/src",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.glm}"
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
        systemversion "latest"

        defines
        {
            "NUM_PLATFORM_WINDOWS",
            "NUM_BUILD_DLL",
            "GLFW_INCLUDE_NONE",
            "_SILENCE_ALL_MS_EXT_DEPRECATION_WARNINGS"
        }

        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
        }

    filter "configurations:Debug"
        defines "NUM_DEBUG"
        runtime "Debug"
        symbols "on"
        
    filter "configurations:Release"
        defines "NUM_RELEASE"
        runtime "Release"
        optimize "on"
    
    filter "configurations:Dist"
        defines "NUM_DIST"
        runtime "Release"
        optimize "on"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
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
        "Number/src",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.glm}"
    }

    links
    {
        "Number"
    }

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "NUM_PLATFORM_WINDOWS",
            "_SILENCE_ALL_MS_EXT_DEPRECATION_WARNINGS"
        }

    filter "configurations:Debug"
        defines "NUM_DEBUG"
        runtime "Debug"
        symbols "on"
        
    filter "configurations:Release"
        defines "NUM_RELEASE"
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines "NUM_DIST"
        runtime "Release"
        optimize "on"