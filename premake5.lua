workspace "Jade"
	configurations {"Debug", "Release"}
	platforms {"x32"}

	startproject "Sandbox"

	includedirs {
		"Engine/include",
		"Dependencies/glm"
	}

	filter "platforms:x32"
		architecture "x32"

	filter "configurations:Debug"
			defines { "DEBUG", "GLEW_STATIC"}
			symbols "On"
		
	filter "configurations:Release"
		defines { "NDEBUG", "GLEW_STATIC" }
		optimize "On"
		
	filter {}

	project "Sandbox"
		kind "ConsoleApp"
		language "C++"
		location "Sandbox"

		files {
			"Sandbox/**.cpp",
			"Sandbox/**.h",
			"Sandbox/assets/shaders/**.frag",
			"Sandbox/assets/shaders/**.vert",
			"Dependencies/stb image/**.h",
			"Sandbox/assets/textures/**.jpg",
			"Sandbox/assets/textures/**.jpeg",
			"Sandbox/assets/textures/**.png",
			"Dependencies/glm/**.hpp"
		}

		includedirs {
			"Dependencies/GLFW/include",
			"Dependencies/glew-2.1.0/include",
			"Sandbox/include",
			"Sandbox/assets/shaders",
			"Dependencies/stb image"
		}

		libdirs {
			"Dependencies/GLFW/lib-vc2022",
			"Dependencies/glew-2.1.0/lib/Release/Win32"
		}

		links {"glfw3", "glew32s", "opengl32", "Engine"}

		targetdir ("Sandbox/build/bin")
		objdir ("Sandbox/build/bin-int")

	project "Engine"
		kind "StaticLib"
		language "C++"
		location "Engine"

		files {
			"Engine/**.cpp", "Engine/**.h",
			"Dependencies/stb image/**.h",
			"Dependencies/glm/**.hpp"
		}

		includedirs {
			"Dependencies/GLFW/include",
			"Dependencies/glew-2.1.0/include",
			"Dependencies/stb image"
		}

		libdirs {
			"Dependencies/GLFW/lib-vc2022",
			"Dependencies/glew-2.1.0/lib/Release/Win32"
		}	

		links {"glfw3", "glew32s", "opengl32"}

		targetdir ("Engine/build/bin")
		objdir ("Engine/build/bin-int")

	project "UnitTests"
		kind "ConsoleApp"
		language "C++"
		location "UnitTests"

		files {
			"UnitTests/**.cpp",
			"UnitTests/**.h",
			"UnitTests/assets/**.txt",
			"UnitTests/assets/**.jpg",
			"UnitTests/assets/**.jpeg",
			"UnitTests/assets/**.png",
			"Dependencies/stb image/**.h"
		}


		includedirs { 
			"UnitTests/include",
			"Dependencies/stb image"
		}

		links { "Engine" }

		targetdir ("UnitTests/build/bin")
		objdir ("UnitTests/build/bin-int")