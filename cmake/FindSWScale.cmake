# - Try to find FFMPEG libswscale
# Once done, this will define
#
#  SWScale_FOUND - the library is available
#  SWScale_INCLUDE_DIRS - the include directories
#  SWScale_LIBRARIES - the libraries
#  SWScale_INCLUDE - the file to include (may be used in config.h)
#
# See documentation on how to write CMake scripts at
# http://www.cmake.org/Wiki/CMake:How_To_Find_Libraries

include(LibFindMacros)

libfind_package(SWScale AVUtil)

libfind_pkg_check_modules(SWScale_PKGCONF libswscale)

find_path(SWScale_INCLUDE_DIR
  NAMES libswscale/swscale.h ffmpeg/swscale.h swscale.h
  PATHS ${SWScale_PKGCONF_INCLUDE_DIRS}
  PATH_SUFFIXES ffmpeg
)

if(SWScale_INCLUDE_DIR)
  foreach(suffix libswscale/ ffmpeg/ "")
    if(NOT SWScale_INCLUDE)
      if(EXISTS "${SWScale_INCLUDE_DIR}/${suffix}swscale.h")
        set(SWScale_INCLUDE "${suffix}swscale.h")
      endif(EXISTS "${SWScale_INCLUDE_DIR}/${suffix}swscale.h")
    endif(NOT SWScale_INCLUDE)
  endforeach(suffix)

  if(NOT SWScale_INCLUDE)
    message(FATAL_ERROR "Found swscale.h include dir, but not the header file. This is an internal error in FindSWScale.cmake")
  endif(NOT SWScale_INCLUDE)
endif(SWScale_INCLUDE_DIR)

find_library(SWScale_LIBRARY
  NAMES swscale
  PATHS ${SWScale_PKGCONF_LIBRARY_DIRS}
)

set(SWScale_PROCESS_INCLUDES SWScale_INCLUDE_DIR AVUtil_INCLUDE_DIRS)
set(SWScale_PROCESS_LIBS SWScale_LIBRARY AVUtil_LIBRARIES)
libfind_process(SWScale)

