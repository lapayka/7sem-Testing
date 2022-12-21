set( PROJECT_NAME DBCW_ut_class )

add_executable( ${PROJECT_NAME} )

target_sources( ${PROJECT_NAME} 
    PRIVATE
        Test.cpp
        testconnect.h
        testconnect.cpp
        mocks/ConfigMock.cpp
        mocks/ConfigMock.h
)

target_include_directories( ${PROJECT_NAME} PRIVATE ${Boost_INCLUDE_DIRS} )

target_link_libraries( ${PROJECT_NAME}
    PRIVATE
        DBCW
        DA
        libpq_MOCK
)

set_target_properties( ${PROJECT_NAME} PROPERTIES VS_DEBUGGER_COMMAND_ARGUMENTS --log_level=all )