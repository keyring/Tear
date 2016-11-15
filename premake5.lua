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

        includedirs {
          "3rdparty/stb"
        }
        files {
            "**.h",
            "**.c",
            "**.cpp",
            "3rdparty/stb/*",
        }

        filter "configurations:Debug"
        defines { "DEBUG" }
        flags { "Symbols" }

        filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"

        configuration "windows"
            links{
              "glfw3",
              "glew32",
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
