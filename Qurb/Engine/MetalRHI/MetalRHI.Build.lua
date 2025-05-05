-- Qurb.MetalRHI

project "MetalRHI"
    kind "SharedLib"
    language "C++"
    cppdialect "C++23"

    targetname "QurbMetalRHI"
    targetdir "%{wks.location}/Binaries/%{cfg.buildcfg}"
    objdir "%{wks.location}/Binaries/Intermediate/%{cfg.buildcfg}"

    files {
        "Public/**.cpp",
        "Public/**.hpp",
        "Private/**.cpp",
        "Private/**.mm",
        "Private/**.hpp",
    }

    defines {
        "QURB_METAL_RHI_EXPORT"
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

    filter { "configurations:Debug" }
        runtime "Debug"
        optimize "Off"
        symbols "On"
        -- defines "DEBUG"
    filter {}

    filter { "configurations:Release" }
        runtime "Release"
        optimize "On"
        symbols "Off"
        -- defines "DEBUG"
    filter {}

