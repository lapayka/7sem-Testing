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
        ObjectMother.h
        ObjectMother.cpp
)

target_link_libraries( ${PROJECT_NAME}
    PRIVATE
        libpq_MOCK
        DA
)

set_target_properties( ${PROJECT_NAME} PROPERTIES VS_DEBUGGER_COMMAND_ARGUMENTS --log_level=all )

add_test_ ( ${PROJECT_NAME} )