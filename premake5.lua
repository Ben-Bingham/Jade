workspace "Jade"
	configurations {"Debug", "Release"}
	platforms {"x32"}

	startproject "Sandbox"

	includedirs {
		"Engine/include"
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
			"Sandbox/assets/shaders/**.vert"
		}

		includedirs {
			"Dependencies/GLFW/include",
			"Dependencies/glew-2.1.0/include",
			"Sandbox/include",
			"Sandbox/assets/shaders"
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

		files {"Engine/**.cpp", "Engine/**.h"}


		includedirs {
			"Dependencies/GLFW/include",
			"Dependencies/glew-2.1.0/include",
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

		files {"UnitTests/**.cpp", "UnitTests/**.h", "UnitTests/assets/**.txt"}


		includedirs { 
			"UnitTests/include"
		}

		links { "Engine" }

		targetdir ("UnitTests/build/bin")
		objdir ("UnitTests/build/bin-int")