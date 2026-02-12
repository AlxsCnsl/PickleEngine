# modules/CMakeLists.txt
# scans each subdirectory and adds it if it contains a CMakeLists.txt
file(GLOB MODULE_DIRS RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}/*")
foreach(md ${MODULE_DIRS})
  if(IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/${md}")
    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${md}/CMakeLists.txt")
      message(STATUS "Adding module: ${md}")
      add_subdirectory("${md}")
    else()
      message(VERBOSE "Skipping ${md} (no CMakeLists.txt)")
    endif()
  endif()
endforeach()
