-- A solution contains projects, and defines the available configurations
solution "foo"
   configurations { "Debug", "Release" }
 
   -- A project defines one build target
   project "foo"
      kind "SharedLib"
	  defines 'FOO_EXPORTS'
      language "C++"
      files { "**.h", "**.cpp" }
 
      configuration "Debug"
         defines { "DEBUG" }
         flags { "Symbols" }
 
      configuration "Release"
         defines { "NDEBUG" }
         flags { "Optimize" }    