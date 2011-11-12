# - Try to find FontConfig
# Once done, this will define
#
#  FontConfig_FOUND - system has FontConfig
#  FontConfig_INCLUDE_DIRS - the FontConfig include directories
#  FontConfig_LIBRARIES - link these to use FontConfig

include(LibFindMacros)

# Use pkg-config to get hints about paths
libfind_pkg_check_modules(FontConfig_PKGCONF fontconfig)

# Include dir
find_path(FontConfig_INCLUDE_DIR
  NAMES fontconfig/fontconfig.h
  PATHS ${FontConfig_PKGCONF_INCLUDE_DIRS}
)

# Finally the library itself
find_library(FontConfig_LIBRARY
  NAMES fontconfig
  PATHS ${FontConfig_PKGCONF_LIBRARY_DIRS}
)

# Set the include dir variables and the libraries and let libfind_process do the rest.
# NOTE: Singular variables for this library, plural for libraries this this lib depends on.
set(FontConfig_PROCESS_INCLUDES FontConfig_INCLUDE_DIR)
set(FontConfig_PROCESS_LIBS FontConfig_LIBRARY)
libfind_process(FontConfig)

