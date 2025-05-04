project "QurbSandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++23"

    targetdir "%{wks.location}/Binaries/%{cfg.buildcfg}"
    objdir "%{wks.location}/Binaries/Intermediate/%{cfg.buildcfg}"

    files {
        "Public/**.cpp",
        "Public/**.hpp",
        "Private/**.cpp",
        "Private/**.hpp",
    }

    links {
        "Core",
        "Runtime",
    }

    includedirs {
        "Public",
        "Private",

        include_dirs["Engine.Core"],
        include_dirs["Engine.Runtime"],
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
            ["ALWAYS_SEARCH_USER_PATHS"] = "YES",
            ["GENERATE_INFOPLIST_FILE"] = "YES",
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
