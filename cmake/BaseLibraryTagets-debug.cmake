#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "BaseLibrary" for configuration "Debug"
set_property(TARGET BaseLibrary APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(BaseLibrary PROPERTIES
  IMPORTED_LOCATION_DEBUG "/data/home/huluwa/study/project/BaseLibrary/install/lib/libBaseLibrary.so"
  IMPORTED_SONAME_DEBUG "libBaseLibrary.so"
  )

list(APPEND _IMPORT_CHECK_TARGETS BaseLibrary )
list(APPEND _IMPORT_CHECK_FILES_FOR_BaseLibrary "/data/home/huluwa/study/project/BaseLibrary/install/lib/libBaseLibrary.so" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
