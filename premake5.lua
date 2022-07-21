workspace "Jade"
	configurations {"Debug", "Release"}
	platforms {"x64"}

	startproject "Sandbox"

	includedirs {
		"Engine/include",
		"Dependencies/GLM"
	}

	filter "platforms:x64"
		architecture "x64"

	filter "configurations:Debug"
			defines { "DEBUG", "GLEW_STATIC", "JADE_DEBUG"}
			symbols "On"
		
	filter "configurations:Release"
		defines { "NDEBUG", "GLEW_STATIC", "JADE_RELEASE" }
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
			"Sandbox/assets/**.jpg",
			"Sandbox/assets/**.jpeg",
			"Sandbox/assets/**.png",
			"Sandbox/assets/**.obj",
			"Sandbox/assets/**.mtl",
			"Engine/include/*.h"
		}

		includedirs {
			"Dependencies/GLFW/include",
			"Dependencies/glew-2.1.0/include",
			"Sandbox/include",
			"Sandbox/assets/shaders",
			"Dependencies/stb image",
			"Dependencies/assimp/include",
			"Dependencies/zlib/include"
		}

		libdirs {
			"Dependencies/GLFW/lib-vc2022",
			"Dependencies/glew-2.1.0/lib/Release/x64",
			"Dependencies/assimp",
			"Dependencies/zlib"
		}

		links {"glfw3", "glew32s", "opengl32", "Engine", "zlibstaticd"}

		filter "configurations:Debug"
			links {"assimp-vc143-mtd"}
		
		filter "configurations:Release"
			links {"assimp-vc143-mt"}
		
		filter {}

		targetdir ("Sandbox/build/bin")
		objdir ("Sandbox/build/bin-int")

	project "Engine"
		kind "StaticLib"
		language "C++"
		location "Engine"

		files {
			"Engine/**.cpp", "Engine/**.h",
			"Engine/assets/**.vert",
			"Engine/assets/**.frag",
		}

		includedirs {
			"Dependencies/GLFW/include",
			"Dependencies/glew-2.1.0/include",
			"Dependencies/stb image",
			"Dependencies/assimp/include",
			"Dependencies/zlib/include"
		}

		libdirs {
			"Dependencies/GLFW/lib-vc2022",
			"Dependencies/glew-2.1.0/lib/Release/x64",
			"Dependencies/assimp",
			"Dependencies/zlib"
		}	

		links {"glfw3", "glew32s", "opengl32", "zlibstaticd"}

		filter "configurations:Debug"
			links {"assimp-vc143-mtd"}
		
		filter "configurations:Release"
			links {"assimp-vc143-mt"}
		
		filter {}

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