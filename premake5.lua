IncludeDir = {}
LibDirs = {}


odinOutputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

workspace "Odin"
    language "C++"
    cppdialect "C++17"
    architecture "x86_64"
    configurations {
        "Debug", 
        "Release"
    }

    filter {"system:windows"}
        links {
            "opengl32"
        }
        staticruntime "On"
        systemversion "latest"

    project "GLAD"
        kind "StaticLib"
        language "C"
        staticruntime "on"
        location "external/GLAD"

        targetdir ("external/GLAD/bin/" .. odinOutputDir .. "/%{prj.name}")
        objdir ("external/GLAD/bin-int/" .. odinOutputDir .. "/%{prj.name}")

        files
        {
            "Odin/include/glad/glad.h",
            "Odin/include/KHR/khrplatform.h",
            "Odin/include/glad/glad_wgl.h",
            "external/GLAD/src/glad.c",
            "external/GLAD/src/glad_wgl.c"
        }

        includedirs
        {
            "Odin/include"
        }


    project "Odin"
        location "Odin"
        kind "StaticLib"

        targetdir ("%{prj.name}/bin/" .. odinOutputDir .. "/%{prj.name}")
        objdir ("%{prj.name}/bin-int/" .. odinOutputDir .. "/%{prj.name}")

        files {
            "%{prj.name}/src/**.cpp",
            "%{prj.name}/include/**.h",
            "%{prj.name}/include/**.hpp"
        }

        includedirs {
            "%{prj.location}/include"
        }

        links {
            "GLAD"
        }

        libdirs {
            
        }

        filter "system:windows"
            cppdialect "C++17"
            staticruntime "On"
            systemversion "latest"

        filter {"configurations:Debug"}
            symbols "On"
            defines {
                "DEBUG"
            }

        filter {"configurations:Release"}
            optimize "On"
            defines {
                "NDEBUG"
            }


        
    project "Sandbox"
        location "Sandbox"
        kind "ConsoleApp"

        targetdir ("%{prj.name}/bin/" .. odinOutputDir .. "/%{prj.name}")
        objdir ("%{prj.name}/bin-int/" .. odinOutputDir .. "/%{prj.name}")

        files {
            "%{prj.name}/src/**.cpp",
            "%{prj.name}/include/**.h",
            "%{prj.name}/include/**.hpp"
        }

        links {
            "Odin"
        }

        includedirs {
            "%{prj.name}/include",
            "Odin/include"
        }

        filter "system:windows"
            cppdialect "C++17"
            staticruntime "On"
            systemversion "latest"

        filter {"configurations:Debug"}
            symbols "On"
            defines {
                "DEBUG"
            }

        filter {"configurations:Release"}
            optimize "On"
            defines {
                "NDEBUG"
            }
