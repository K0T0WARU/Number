workspace "Number"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Number"
    location "Number"
    kind "SharedLib"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "Number/vendor/spdlog/include"
    }

    filter "system:windows"
        cppdialect "C++20"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "NUM_PLATFORM_WINDOWS",
            "NUM_BUILD_DLL"
        }

        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
        }

    filter "configurations:Debug"
        defines "NUM_DEBUG"
        symbols "On"
        
    filter "configurations:Release"
        defines "NUM_RELEASE"
        optimize "On"
    
    filter "configurations:Dist"
        defines "NUM_DIST"
        optimize "On"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"

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
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "NUM_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "NUM_DEBUG"
        symbols "On"
        
    filter "configurations:Release"
        defines "NUM_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "NUM_DIST"
        optimize "On"