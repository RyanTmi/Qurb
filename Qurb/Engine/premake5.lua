include "Core/Core.Build.lua"
include "Runtime/Runtime.Build.lua"

filter { "system:macosx" }
    include "MetalRHI/MetalRHI.Build.lua"
filter {}
