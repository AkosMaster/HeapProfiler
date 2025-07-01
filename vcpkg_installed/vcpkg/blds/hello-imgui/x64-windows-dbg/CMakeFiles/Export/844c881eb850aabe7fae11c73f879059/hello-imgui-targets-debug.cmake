#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "hello-imgui::stb_hello_imgui" for configuration "Debug"
set_property(TARGET hello-imgui::stb_hello_imgui APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(hello-imgui::stb_hello_imgui PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/stb_hello_imgui.lib"
  )

list(APPEND _cmake_import_check_targets hello-imgui::stb_hello_imgui )
list(APPEND _cmake_import_check_files_for_hello-imgui::stb_hello_imgui "${_IMPORT_PREFIX}/lib/stb_hello_imgui.lib" )

# Import target "hello-imgui::hello_imgui" for configuration "Debug"
set_property(TARGET hello-imgui::hello_imgui APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(hello-imgui::hello_imgui PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "C;CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/hello_imgui.lib"
  )

list(APPEND _cmake_import_check_targets hello-imgui::hello_imgui )
list(APPEND _cmake_import_check_files_for_hello-imgui::hello_imgui "${_IMPORT_PREFIX}/lib/hello_imgui.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
