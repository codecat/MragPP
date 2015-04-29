if(NOT WIN32)
	set(CMAKE_CXX_FLAGS "-std=c++0x")
endif()

add_subdirectory(Scratch)

file(GLOB_RECURSE box2d_sources "Box2D/*.cpp" "Box2D/*.c" "Box2D/*.h")

add_library(Mragpp
	Function.h
	SpecialMath.h
	AnimationSheet.cpp AnimationSheet.h
	Colors.cpp Colors.h
	ContentRegister.cpp ContentRegister.h
	Easing.cpp Easing.h
	Engine.cpp Engine.h
	Font.cpp Font.h
	Game.cpp Game.h
	Input.cpp Input.h InputKeys.h
	Line.cpp Line.h
	Matrix.cpp Matrix.h
	Message.cpp Message.h
	Path.cpp Path.h
	Paths.cpp Paths.h
	Rectangle.cpp Rectangle.h
	Renderer.cpp Renderer.h
	Settings.cpp Settings.h
	Texture.cpp Texture.h
	Vector.cpp Vector.h
	Window.cpp Window.h
	Pathfinding/Node.cpp Pathfinding/Node.h
	Pathfinding/Pathfinding.cpp Pathfinding/Pathfinding.h
	Pathfinding/Tile.cpp Pathfinding/Tile.h
	Xml/XmlFile.cpp Xml/XmlFile.h
	Xml/XmlHelpers.cpp Xml/XmlHelpers.h
	Xml/XmlTag.cpp Xml/XmlTag.h
	${box2d_sources})

source_group(Sources REGULAR_EXPRESSION ".*")
source_group(Pathfinding REGULAR_EXPRESSION "Pathfinding/.*")
source_group(Xml REGULAR_EXPRESSION "Xml/.*")
source_group(Box2D REGULAR_EXPRESSION "Box2D/.*")

if(UNIX AND NOT APPLE)
	find_library(M_LIB m)
	target_link_libraries(Mragpp ${M_LIB})
endif()

find_package(OpenGL REQUIRED)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

include_directories(.
	./Scratch/src/
	${SDL2_INCLUDE_DIR}
	${SDL2_IMAGE_INCLUDE_DIR}
	${SDL2_TTF_INCLUDE_DIR}
	${OPENGL_INCLUDE_DIR})
target_link_libraries(Mragpp
	Scratch
	${SDL2_LIBRARY}
	${SDL2_IMAGE_LIBRARY}
	${SDL2_TTF_LIBRARY}
	${OPENGL_LIBRARIES})

set_target_properties(Mragpp PROPERTIES MACOSX_RPATH 1)
set_target_properties(Mragpp PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")
set_target_properties(Mragpp PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")
