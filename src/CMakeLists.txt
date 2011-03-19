# Find all *.cc and *.hh files (store them in variables SOURCE_FILES and HEADER_FILES)
FILE(GLOB SOURCE_FILES "*.cc")
FILE(GLOB HEADER_FILES "*.hh")

# Define SOURCES variable so that it contains all the files
set(SOURCES ${SOURCE_FILES} ${HEADER_FILES})

# Set default compile flags for GCC
if(CMAKE_COMPILER_IS_GNUCXX)
	message(STATUS "GCC detected, enabling pedantic mode and warnings")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++98")
endif()

# Generate config.h from config.h.in
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/config.h.in" "${CMAKE_CURRENT_BINARY_DIR}/config.h" @ONLY)
include_directories("${CMAKE_CURRENT_BINARY_DIR}")

# Libraries

# An example of how to use a library
find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
set(LIBS ${LIBS} ${Boost_LIBRARIES})

# Irrlicht
find_package(Irrlicht REQUIRED)
include_directories(${Irrlicht_INCLUDE_DIRS})
set(LIBS ${LIBS} ${Irrlicht_LIBRARIES})

# Build an executable named the same as the project short name.
# If you need more, you'll need to alter this script by repeating the following
# three lines for each executable (with the necessary changes)
add_executable(${PROJECT_SHORT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_SHORT_NAME} ${LIBS})
install(TARGETS "${PROJECT_SHORT_NAME}" DESTINATION bin)

