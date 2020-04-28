IncludeDir = {}
LibDirs = {}
RenderAPI = "Vulkan"


odinOutputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

workspace "Odin"
    language "C++"
    cppdialect "C++17"
    architecture "x86_64"
    staticruntime "on"
    systemversion "latest"
    configurations {
        "Debug", 
        "Release"
    }


    filter {"system:windows"}
        --if RenderAPI == "OpenGL" then
            links {
                "opengl32"
            }
        --end
        
        defines {
            "_CRT_SECURE_NO_WARNINGS"
        }

    filter {"system:linux"}
        toolset "gcc"
        links {
            "GL",
            "X11"
        }

    project "Odin"
        location "Odin"
        kind "StaticLib"

        if RenderAPI == "OpenGL" then
            defines {
                "ODIN_RENDERAPI_OPENGL"
            }
        elseif RenderAPI == "DirectX" then
            defines {
                "ODIN_RENDERAPI_DIRECTX"
            }

        elseif RenderAPI == "Vulkan" then
            defines {
                "ODIN_RENDERAPI_VULKAN"
            }
            links {
                "vulkan-1"
            }
        end
        
        warnings "Extra"

        targetdir ("%{prj.name}/bin/" .. odinOutputDir .. "/%{prj.name}")
        objdir ("%{prj.name}/bin-int/" .. odinOutputDir .. "/%{prj.name}")

        

        files {
            "%{prj.name}/src/**.cpp",
            "%{prj.name}/src/**.c",
            "%{prj.name}/include/**.h",
            "%{prj.name}/include/**.hpp"
        }

        includedirs {
            "%{prj.location}/include"
        }


        filter "system:windows"
            cppdialect "C++17"
            staticruntime "On"
            systemversion "latest"

            excludes {
                "%{prj.name}/include/glad/glad_glx.h",
                "%{prj.name}/src/glad/glad_glx.c"
            }

            libdirs {
                "external/lib/win32"
            }

            

        filter "system:linux"
        excludes {
            "%{prj.name}/include/glad/glad_wgl.h",
            "%{prj.name}/src/glad/glad_wgl.c"
        }

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
        kind "WindowedApp"

        targetdir ("%{prj.name}/bin/" .. odinOutputDir .. "/%{prj.name}")
        objdir ("%{prj.name}/bin-int/" .. odinOutputDir .. "/%{prj.name}")

        if RenderAPI == "OpenGL" then
            defines {
                "ODIN_RENDERAPI_OPENGL"
            }
        elseif RenderAPI == "DirectX" then
            defines {
                "ODIN_RENDERAPI_DIRECTX"
            }

        elseif RenderAPI == "Vulkan" then
            defines {
                "ODIN_RENDERAPI_VULKAN"
            }
        end

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
