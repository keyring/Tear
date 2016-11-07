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
        defines { "DEBUG","GLEW_STATIC" }
        flags { "Symbols" }

        filter "configurations:Release"
        defines { "NDEBUG", "GLEW_STATIC" }
        optimize "On"

        configuration "windows"
            links{
              "glfw3",
              "glew32s",
                "OpenGL32"
            }
        configuration "linux"
            links{
              "glfw3",
              "GLEW",
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
