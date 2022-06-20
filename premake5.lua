workspace "Jade"
	configurations {"Debug", "Release"}
	platforms {"x32"}

	startproject "Sandbox"

	files {"**.cpp", "**.h"}

	libdirs {
		"Dependencies/GLFW/lib-vc2022",
		"Dependencies/glew-2.1.0/lib/Release/Win32"
	}

	includedirs {
			"Dependencies/GLFW/include",
			"Dependencies/glew-2.1.0/include",
			"Engine/include"
	}

	links {"glfw3", "glew32s", "opengl32"}

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

		includedirs {
			"Sandbox/include"
		}

		links {"Engine"}

		targetdir ("Sandbox/build/bin")
		objdir ("Sandbox/build/bin-int")

	project "Engine"
		kind "StaticLib"
		language "C++"
		location "Engine"

		targetdir ("Engine/build/bin")
		objdir ("Engine/build/bin-int")
