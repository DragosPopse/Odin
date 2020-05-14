IncludeDir = {}
LibDirs = {}
RenderAPI = "OpenGL"

if os.target() == "windows" then
    glLib = "opengl32"
elseif os.target() == "linux" then
    glLib = "GL"
end


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
        defines {
            "_CRT_SECURE_NO_WARNINGS"
        }

    filter {"system:linux"}
        toolset "gcc"
        links {
            "X11"
        }

    project "Odin"
        location "Odin"
        kind "StaticLib"

        files {
            "%{prj.name}/src/**.cpp",
            "%{prj.name}/src/**.c",
            "%{prj.name}/include/**.h",
            "%{prj.name}/include/**.hpp",
            "%{prj.name}/src/**.hpp"
        }

        includedirs {
            "%{prj.location}/include",
            "%{prj.location}/src"
        }

        if RenderAPI == "OpenGL" then
            defines {
                "ODIN_RENDERAPI_OPENGL"
            }
            links {
                glLib
            }
            excludes {
                "%{prj.name}/src/odin/graphics/vk/**.cpp",
                "%{prj.name}/src/odin/graphics/vk/**.hpp"
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
            excludes {
                "%{prj.name}/src/odin/graphics/opengl/**.cpp",
                "%{prj.name}/src/odin/graphics/opengl/**.hpp"
            }
        end
        
        warnings "Extra"

        targetdir ("%{prj.name}/bin/" .. odinOutputDir .. "/%{prj.name}")
        objdir ("%{prj.name}/bin-int/" .. odinOutputDir .. "/%{prj.name}")

        

        


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
