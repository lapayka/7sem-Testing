set ( PROJECT_NAME Main )

project ( ${PROJECT_NAME} CXX )

set ( Source_Files
    ConfigFactory.cpp
    DBCW.cpp
)

set ( Header_Files 
    ConfigFactory.h
    Login.h
)

set ( all_sources ${Source_Files} ${Header_Files} )

add_executable( ${PROJECT_NAME} ${all_sources} )

target_include_directories( ${PROJECT_NAME} PRIVATE ../DA ../Interface ../DBCW ../WebWrapper)

target_link_libraries( ${PROJECT_NAME}
    PUBLIC
        PostgreSQL::PostgreSQL
        DA
        DBCW
        Interface
        WebWrapper
        jwt
)
