cmake_minimum_required(VERSION 2.8.9)
project(Mrag++)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules/")

if(CMAKE_BUILD_TYPE)
	if(${CMAKE_BUILD_TYPE} STREQUAL Debug)
		message("Mrag++ debug build")
		add_definitions(-DDEBUG)
	else()
		message("Mrag++ release build")
	endif()
else()
	message("Mrag++ release build")
endif()

if(NOT WIN32)
	set(CMAKE_CXX_FLAGS "-std=c++0x")
endif()

add_subdirectory(Mragpp/Scratch)

file(GLOB_RECURSE box2d_sources "Mragpp/Box2D/*.cpp" "Mragpp/Box2D/*.c" "Mragpp/Box2D/*.h")
file(GLOB_RECURSE spine_sources "Mragpp/spine/*.c" "Mragpp/spine/*.h")

add_library(Mragpp
	Mragpp/Function.h
	Mragpp/SpecialMath.h
	Mragpp/AnimationSheet.cpp Mragpp/AnimationSheet.h
	Mragpp/AnimationAtlas.cpp Mragpp/AnimationAtlas.h
	Mragpp/AnimationJson.cpp Mragpp/AnimationJson.h
	Mragpp/Colors.cpp Mragpp/Colors.h
	Mragpp/ContentRegister.cpp Mragpp/ContentRegister.h
	Mragpp/Easing.cpp Mragpp/Easing.h
	Mragpp/Engine.cpp Mragpp/Engine.h
	Mragpp/Font.cpp Mragpp/Font.h
	Mragpp/Game.cpp Mragpp/Game.h
	Mragpp/Input.cpp Mragpp/Input.h Mragpp/InputKeys.h
	Mragpp/Line.cpp Mragpp/Line.h
	Mragpp/Matrix.cpp Mragpp/Matrix.h
	Mragpp/Message.cpp Mragpp/Message.h
	Mragpp/Path.cpp Mragpp/Path.h
	Mragpp/Paths.cpp Mragpp/Paths.h
	Mragpp/Rectangle.cpp Mragpp/Rectangle.h
	Mragpp/Renderer.cpp Mragpp/Renderer.h
	Mragpp/Settings.cpp Mragpp/Settings.h
	Mragpp/Texture.cpp Mragpp/Texture.h
	Mragpp/Vector.cpp Mragpp/Vector.h
	Mragpp/Window.cpp Mragpp/Window.h
	Mragpp/Sound.cpp Mragpp/Sound.h
	Mragpp/SoundChannel.cpp Mragpp/SoundChannel.h
	Mragpp/Music.cpp Mragpp/Music.h
	Mragpp/Pathfinding/Node.cpp Mragpp/Pathfinding/Node.h
	Mragpp/Pathfinding/Pathfinding.cpp Mragpp/Pathfinding/Pathfinding.h
	Mragpp/Pathfinding/Tile.cpp Mragpp/Pathfinding/Tile.h
	Mragpp/Xml/XmlFile.cpp Mragpp/Xml/XmlFile.h
	Mragpp/Xml/XmlHelpers.cpp Mragpp/Xml/XmlHelpers.h
	Mragpp/Xml/XmlTag.cpp Mragpp/Xml/XmlTag.h
	${box2d_sources}
	${spine_sources}
)

source_group(Sources REGULAR_EXPRESSION "Mragpp/.*")
source_group(Pathfinding REGULAR_EXPRESSION "Mragpp/Pathfinding/.*")
source_group(Xml REGULAR_EXPRESSION "Mragpp/Xml/.*")
source_group(Box2D REGULAR_EXPRESSION "Mragpp/Box2D/.*")
source_group(Spine REGULAR_EXPRESSION "Mragpp/spine/.*")

if(UNIX AND NOT APPLE)
	find_library(M_LIB m)
	target_link_libraries(Mragpp ${M_LIB})
endif()

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)

include_directories(.
	Mragpp/
	Mragpp/Scratch/
	${SDL2_INCLUDE_DIR}
	${SDL2_IMAGE_INCLUDE_DIR}
	${SDL2_TTF_INCLUDE_DIR}
	${SDLMIXER_INCLUDE_DIR}
	${OPENGL_INCLUDE_DIR}
	${GLEW_INCLUDE_DIRS}
)
target_link_libraries(Mragpp
	Scratch
	${SDL2_LIBRARY}
	${SDL2_IMAGE_LIBRARY}
	${SDL2_TTF_LIBRARY}
	${SDLMIXER_LIBRARY}
	${OPENGL_LIBRARIES}
	${GLEW_LIBRARIES}
	stdc++
)

set_target_properties(Mragpp PROPERTIES MACOSX_RPATH 1)
set_target_properties(Mragpp PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")
set_target_properties(Mragpp PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")

add_subdirectory(examples)
