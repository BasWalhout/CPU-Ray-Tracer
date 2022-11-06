function UseVisualStudio(action)
	return string.find(action, "vs") ~= nil;
end

function UseGMake(action)
	return not string.find(action, "gmake") ~= nil;
end

function UseCodeLite(action)
	return action == "codelite";
end

function UseXCode(action)
	return action == "xcode4";
end



if(	UseVisualStudio(_ACTION) 	or
	UseCodeLite(_ACTION) 		or
	UseGMake(_ACTION) 			or
	UseXCode(_ACTION))
then

	workspace("CPU-Ray-Tracer")

		location("Workspace_" .. _ACTION)

		configurations({"Debug", "Release"})

		platforms({"Win32", "Win64"})

		language("C++")

		startproject("Ray-Tracer")

		targetdir("%{prj.location}/bin/%{cfg.platform}/%{cfg.buildcfg}/%{prj.name}")
		debugdir("%{prj.location}/bin/%{cfg.platform}/%{cfg.buildcfg}/%{prj.name}")

		filter({"configurations:Debug"})
			defines({"DEBUG", "_DEBUG"})
			symbols("On")

		filter({"configurations:Release"})
			defines({"NDEBUG"})
			optimize("On")

		filter({"platforms:Win32"})
			system("Windows")
			architecture("x86")

		filter({"platforms:Win64"})
			system("Windows")
			architecture("x86_64")

	-- MathLibrary Project -----------------------------------------

	project("MathLibrary")

		kind("StaticLib")

		files({"MathLibrary/*.cpp", "MathLibrary/*.h"})

	-- MathTest Project --------------------------------------------

	--TODO: Make sure that building for microsoft visual studio test framework is possible.

	if(UseVisualStudio(_ACTION))
	then

		project("MathTests")

			kind("SharedLib")

			links({"MathLibrary"})

			dependson({"MathLibrary"})

			externalincludedirs({
				"$(VCInstallDir)/Auxiliary/VS/UnitTest/include", 
				"MathLibrary"
			})

			syslibdirs({"$(VCInstallDir)/Auxiliary/VS/UnitTest/lib"})

			files({"MathTest/*.cpp", "MathTest/*.h"})
	end

	-- Ray-Tracer Project -----------------------------------------

	project("Ray-Tracer")

		kind("ConsoleApp")

		links({
			"MathLibrary", 
			"SDL2", 
			"SDL2main"
		})

		dependson({"MathLibrary"})

		includedirs({
			"Deps/SDL2-2.0.9/include", 
			"MathLibrary"
		})

		files({
			"RayTracer/src/*.cpp", 
			"RayTracer/src/headers/*.h"
		})

		filter({"platforms:Win32"})
			libdirs({"%{prj.location}/../Deps/SDL2-2.0.9/lib/x86/"})

		filter({"platforms:Win64"})
			libdirs({"%{prj.location}/../Deps/SDL2-2.0.9/lib/x64/"})

		filter({"system:windows", "platforms:Win32"})
			postbuildcommands({
				"(robocopy " ..
				"%{prj.location}/../Deps/SDL2-2.0.9/lib/x86 " .. 
				"%{prj.location}/bin/%{cfg.platform}/%{cfg.buildcfg}/%{prj.name} " .. 
				"SDL2.dll)" .. 
				"& IF %ERRORLEVEL% LSS 8 SET ERRORLEVEL = 0"
			})

		filter({"system:windows", "platforms:Win64"})
			postbuildcommands({
				"(robocopy " ..
				"%{prj.location}/../Deps/SDL2-2.0.9/lib/x64 " .. 
				"%{prj.location}/bin/%{cfg.platform}/%{cfg.buildcfg}/%{prj.name} " .. 
				"SDL2.dll)" .. 
				"& IF %ERRORLEVEL% LSS 8 SET ERRORLEVEL = 0"
			})
end