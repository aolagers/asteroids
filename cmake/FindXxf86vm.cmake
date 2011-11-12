include(LibFindMacros)

find_path(Xxf86vm_INCLUDE_DIR NAMES X11/extensions/xf86vmode.h)
find_library(Xxf86vm_LIBRARY NAMES Xxf86vm)

set(Xxf86vm_PROCESS_INCLUDES Xxf86vm_INCLUDE_DIR)
set(Xxf86vm_PROCESS_LIBS Xxf86vm_LIBRARY)

libfind_process(Xxf86vm)

