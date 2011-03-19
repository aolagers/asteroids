set(PROJECT_SHORT_NAME "asteroids")
set(PROJECT_LONG_NAME "Asteroids 3D")
set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 1)

project(${PROJECT_SHORT_NAME})
cmake_minimum_required(VERSION 2.6)

# Avoid source tree pollution
if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
	message(FATAL_ERROR "In-source builds are not permitted. Make a separate folder for building:\nmkdir build; cd build; cmake ..\nBefore that, remove the files already created:\nrm -rf CMakeCache.txt CMakeFiles")
endif()

# Where to install project data files
set(PROJECT_DATA_DIR "${CMAKE_INSTALL_PREFIX}/share/${PROJECT_SHORT_NAME}")

# Where to look for Find*.cmake and other modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

# Add a sensible build type default and warning because empty means no optimization and no debug info.
if(NOT CMAKE_BUILD_TYPE)
	message("WARNING: CMAKE_BUILD_TYPE is not defined!\n         Defaulting to CMAKE_BUILD_TYPE=Release. Use ccmake to set a proper value.")
	set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel." FORCE)
endif()

add_subdirectory(src)
add_subdirectory(data)

