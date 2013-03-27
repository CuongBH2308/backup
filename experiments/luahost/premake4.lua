solution "luahost"
	configurations {"Debug", "Release"}

	project "luahost"
		kind "ConsoleApp"
		language "C++"
		files {"**.h", "**.cpp"}
		buildoptions {"-std=c++0x"}
		links {"lua", "dl"}
		postbuildcommands{"luac -o startup.lub startup.lua"}
		
		configuration "Debug"
			defines {"DEBUG"}
			flags{"Symbols"}
		
		configuration "Release"
			defines {"NDEBUG"}
			flags {"Optimize"}

