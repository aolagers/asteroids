include(LibFindMacros)

libfind_package(Irrlicht OpenGL)
libfind_package(Irrlicht Xxf86vm)
libfind_package(Irrlicht SDL)
libfind_package(Irrlicht SDL_mixer)

find_path(Irrlicht_INCLUDE_DIR NAMES irrlicht.h PATH_SUFFIXES irrlicht PATHS /usr/include/irrlicht /usr/local/include/irrlicht /usr/local/include /p/contrib/include/irrlicht )
find_library(Irrlicht_LIBRARY NAMES Irrlicht PATHS /usr/lib /usr/local/lib /p/contrib/lib)

set(Irrlicht_PROCESS_INCLUDES Irrlicht_INCLUDE_DIR OpenGL_INCLUDE_DIRS Xxf86vm_INCLUDE_DIRS SDL_INCLUDE_DIRS SDL_mixer_INCLUDE_DIRS)
set(Irrlicht_PROCESS_LIBS Irrlicht_LIBRARY OpenGL_LIBRARIES Xxf86vm_LIBRARIES SDL_LIBRARIES SDL_mixer_LIBRARIES)

libfind_process(Irrlicht)

