set ( PROJECT_NAME Interface )

project ( ${PROJECT_NAME} CXX )

set ( Source_Files
    UserInterface.cpp
    View.cpp
)

set ( Header_Files 
    AdminInterface.h
    ArtistInterface.h
    BaseInterface.h
    UserInterface.h
    View.h
)

set ( all_sources ${Source_Files} ${Header_Files} )

add_library( ${PROJECT_NAME} STATIC ${all_sources} )

target_include_directories( ${PROJECT_NAME} PRIVATE  ../DBCW)

target_link_libraries( ${PROJECT_NAME}
    PUBLIC
        DBCW
)