add_subdirectory( libpqPLUG )

set( PROJECT_NAME DA_ut )

add_executable( ${PROJECT_NAME} )

target_sources( ${PROJECT_NAME} 
    PRIVATE
        RepoTests.cpp
        TestConfig.cpp
        TestConfig.h
        TestConnect.cpp
        TestConnect.h
)

target_link_libraries( ${PROJECT_NAME}
    PRIVATE
        libpq_MOCK
        DA
)