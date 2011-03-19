# Match all files, except hidden ones (which begin with dot).
file(GLOB_RECURSE DATA_FILES "share/[^.]*")

#file(GLOB DATA_FILES "share/[^.]*")

if(DATA_FILES)
	install(FILES ${DATA_FILES} DESTINATION "${PROJECT_DATA_DIR}")
endif()

