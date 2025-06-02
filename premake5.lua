include_dirs = {}
include_dirs["Engine.Core"] = "%{wks.location}/Qurb/Engine/Core/Public"
include_dirs["Engine.Runtime"] = "%{wks.location}/Qurb/Engine/Runtime/Public"
include_dirs["ThirdParty.stb"] = "%{wks.location}/Qurb/ThirdParty/stb/Public"

workspace "Qurb"
    configurations { "Debug", "Release" }

    filter { "system:macosx" }
        architecture "ARM64"
    filter {}

    filter { "system:windows or linux" }
        architecture "x86_64"
    filter {}

    group "Engine"
        include "Qurb/Engine"
    group ""

    group "Samples"
        include "Samples/QurbSandbox/QurbSandbox.Build.lua"
    group ""

    group "ThirdParty"
        include "Qurb/ThirdParty"
    group ""
