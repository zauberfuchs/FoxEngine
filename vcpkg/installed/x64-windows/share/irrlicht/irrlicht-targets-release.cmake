#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Irrlicht" for configuration "Release"
set_property(TARGET Irrlicht APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(Irrlicht PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/Irrlicht.lib"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/Irrlicht.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS Irrlicht )
list(APPEND _IMPORT_CHECK_FILES_FOR_Irrlicht "${_IMPORT_PREFIX}/lib/Irrlicht.lib" "${_IMPORT_PREFIX}/bin/Irrlicht.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
