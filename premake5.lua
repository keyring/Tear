-- premake5.lua
workspace "TxxE"
configurations { "Debug", "Release" }
location "build"

project "TxxE"
kind "WindowedApp"
language "C++"
location "build/TxxE"
libdirs {"libs", "/usr/local/lib"}
links {"glfw3", "X11", "Xrandr", "Xi", "Xinerama", "Xxf86vm", "Xcursor", "GL", "pthread", "dl"}
targetdir "bin/%{cfg.buildcfg}"

files { "**.h", "**.c", "**.cpp" }

filter "configurations:Debug"
defines { "DEBUG" }
flags { "Symbols" }

filter "configurations:Release"
defines { "NDEBUG" }
optimize "On"
