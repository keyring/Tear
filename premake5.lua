-- premake5.lua
workspace "TearEngine"
    configurations { "Debug", "Release" }
    platforms {"x64", "x86"}
    location "build"

    project "TearEngine"
        kind "WindowedApp"
        language "C++"
        location "build/TearEngine"

        targetdir "bin/%{cfg.buildcfg}"

        files { "**.h", "**.c", "**.cpp" }

        filter "configurations:Debug"
        defines { "DEBUG" }
        flags { "Symbols" }

        filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"

        configuration "windows"
            links{
                "glfw3",
                "OpenGL32"
            }
        configuration "linux"
            links{
                "glfw3", 
                "X11",
                "Xrandr",
                "Xi", 
                "Xinerama",
                "Xxf86vm", 
                "Xcursor", 
                "GL", 
                "pthread", 
                "dl"
            }
