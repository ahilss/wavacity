# Include the modules that we'll build

if( NOT CMAKE_SYSTEM_NAME MATCHES "Windows" )
add_subdirectory( mod-null )
add_subdirectory( mod-nyq-bench )
endif()

if( NOT WASM )
add_subdirectory( mod-script-pipe )
endif()


if( NOT CMAKE_SYSTEM_NAME MATCHES "Darwin" )
   if( NOT "${CMAKE_GENERATOR}" MATCHES "Visual Studio*")
      install( DIRECTORY "${_DEST}/modules"
               DESTINATION "${_PKGDATA}" )
   endif()
endif()

