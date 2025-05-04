project "Runtime"
    kind "SharedLib"
    language "C++"
    cppdialect "C++23"

    targetname "QurbRuntime"
    targetdir "%{wks.location}/Binaries/%{cfg.buildcfg}"
    objdir "%{wks.location}/Binaries/Intermediate/%{cfg.buildcfg}"

    files {
        "Public/**.cpp",
        "Public/**.hpp",
        "Private/**.cpp",
        "Private/**.mm",
        "Private/**.hpp",
    }

    links {
        "Core",
    }

    includedirs {
        "Public",
        "Private",

        include_dirs["Engine.Core"],
    }

    filter { "system:macosx" }
        links {
            "AppKit.framework",
            "Cocoa.framework",
            "Foundation.framework",
            "Metal.framework",
            "MetalKit.framework",
            "QuartzCore.framework",
        }

        xcodebuildsettings {
            ["USE_HEADERMAP"] = "NO",
            ["ALWAYS_SEARCH_USER_PATHS"] = "YES"
        }
    filter {}

    filter { "configurations:Debug" }
        runtime "Debug"
        optimize "Off"
        symbols "On"
    filter {}

    filter { "configurations:Release" }
        runtime "Release"
        optimize "On"
        symbols "Off"
    filter {}
