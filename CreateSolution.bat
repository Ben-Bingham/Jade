DEL /S *.sln
DEL /S *.vcxproj
DEL /S *.vcxproj.filters
DEL /S *.vcxproj.user
DEL /q .vs

CALL Dependencies\premake\premake5.exe vs2022

set result="false"

if not exist Dependencies\assimp\assimp-vc143-mt.lib set result="true"
if not exist Dependencies\assimp\assimp-vc143-mtd.lib set result="true"

if %result%=="true" (
	DEL /q Dependencies\assimp\assimp-vc143-mt.lib
	DEL /q Dependencies\assimp\assimp-vc143-mtd.lib
	cd Dependencies\assimp\assimp-5.2.4
	RMDIR /s /q build
	mkdir build
	cd build
	CALL cmake -DBUILD_SHARED_LIBS=OFF ../
	CALL cmake --build . --config Release
	CALL cmake --build . --config Debug
	move lib\Release\assimp-vc143-mt.lib ..\..\
	move lib\Debug\assimp-vc143-mtd.lib ..\..\
)

