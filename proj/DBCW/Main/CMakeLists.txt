set ( PROJECT_NAME Main )

project ( ${PROJECT_NAME} CXX )

set ( Source_Files
    ConfigFactory.cpp
    DBCW.cpp
)

set ( Header_Files 
    ConfigFactory.h
)

set ( all_sources ${Source_Files} ${Header_Files} )

add_executable( ${PROJECT_NAME} ${all_sources} )

target_include_directories( ${PROJECT_NAME} PRIVATE ${PostgreSQL_INCLUDE_DIRS} ../DA ../Interface ../DBCW)

target_link_libraries( ${PROJECT_NAME}
    PUBLIC
        ${PostgreSQL_LIBRARIES}
        DA
        DBCW
        Interface
)
