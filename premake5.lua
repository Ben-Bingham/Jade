workspace "Jade"
	configurations {"Debug", "Release"}
	platforms {"x32"}

	filter "platforms:x32"
		architecture "x32"

	filter {}

	project "Engine"
		kind "WindowedApp"
		language "C++"
		location "Engine"

		includedirs {
			"Engine/include/**",
			"Dependencies/GLFW/include**",
			"Dependencies/glew-2.1.0/include**"
		}

		files {"**.cpp", "**.h"}

		libdirs {
			"Dependencies/GLFW/lib-vc2022",
			"Dependencies/glew-2.1.0/lib/Release/Win32"
		}

		links {"glfw3", "glew32s", "opengl32"}

		targetdir ("Engine/build/bin")
		objdir ("Engine/build/bin-int")

		filter "configurations:Debug"
			defines { "DEBUG", "GLEW_STATIC"}
			symbols "On"

		filter "configurations:Release"
			defines { "NDEBUG", "GLEW_STATIC" }
			optimize "On"

		filter {}

	project "Sandbox"
		kind "WindowedApp"
		language "C++"
		location "Sandbox"

		includedirs {
			"Engine/include/**",
			"Dependencies/GLFW/include**",
			"Dependencies/glew-2.1.0/include**"
		}

		files {"**.cpp", "**.h"}

		libdirs {
			"Dependencies/GLFW/lib-vc2022",
			"Dependencies/glew-2.1.0/lib/Release/Win32"
		}

		links {"glfw3", "glew32s", "opengl32", "Engine"}

		targetdir ("Sandbox/build/bin")
		objdir ("Sandbox/build/bin-int")

		filter "configurations:Debug"
			defines { "DEBUG", "GLEW_STATIC"}
			symbols "On"

		filter "configurations:Release"
			defines { "NDEBUG", "GLEW_STATIC" }
			optimize "On"

		filter {}
