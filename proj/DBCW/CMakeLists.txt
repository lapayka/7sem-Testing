cmake_minimum_required(VERSION 3.16)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

include ( libs )

set ( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/64/bin )

add_subdirectory( DBCW )
add_subdirectory( DA )
add_subdirectory( Interface )
add_subdirectory( Main )
add_subdirectory( WebWrapper )
