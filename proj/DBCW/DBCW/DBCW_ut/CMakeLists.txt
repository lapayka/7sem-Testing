set( PROJECT_NAME DBCW_ut )

add_executable( ${PROJECT_NAME} )

target_sources( ${PROJECT_NAME} 
    PRIVATE
        Test.cpp
        mocks/ConfigMock.cpp
)

target_include_directories( ${PROJECT_NAME} PRIVATE ${Boost_INCLUDE_DIRS} )

target_link_libraries( ${PROJECT_NAME}
    PRIVATE
        DBCW
        ${Boost_LIBRARIES}
)

set_target_properties( ${PROJECT_NAME} PROPERTIES VS_DEBUGGER_COMMAND_ARGUMENTS --log_level=all )

add_test_( ${PROJECT_NAME} )