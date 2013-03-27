-- A solution contains projects, and defines the available configurations
solution "bar"
   configurations { "Debug", "Release" }
 
   -- A project defines one build target
   project "bar"
      kind "ConsoleApp"
      language "C++"
      files { "**.h", "**.cpp" }
	  includedirs '../foo'
	  libdirs '../foo'
	  links 'foo'
 
      configuration "Debug"
         defines { "DEBUG" }
         flags { "Symbols" }
 
      configuration "Release"
         defines { "NDEBUG" }
         flags { "Optimize" }    