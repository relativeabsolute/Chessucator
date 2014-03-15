solution "Chessucator"
    configurations { "Debug", "Release" }

    project "Chessucator"
        kind "ConsoleApp"
        language "C++"
        includedirs { "include" }
        files { "src/*.cpp"}
        links { "SDL2", "SDL2_ttf", "SDL2_image" }

        configuration {"linux", "gmake"}
            buildoptions {"--std=c++11"}

        configuration "Debug"
            defines { "DEBUG" }
            flags { "Symbols" }

        configuration "Release"
            defines { "NDEBUG" }
            flags { "Optimize" }