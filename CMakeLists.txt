cmake_minimum_required(VERSION 2.8.9)
project(Mrag++)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

if(${CMAKE_BUILD_TYPE} STREQUAL Debug)
	message("Mrag++ debug build")
	add_definitions(-DDEBUG)
else()
	message("Mrag++ release build")
endif()

add_subdirectory(src)
