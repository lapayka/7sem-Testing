set( PROJECT_NAME DBCW_int )

add_executable( ${PROJECT_NAME} )

target_sources( ${PROJECT_NAME} 
    PRIVATE
        Test.cpp
        TestConfig.cpp
        TestConfig.h
        TestConnect.cpp
        TestConnect.h
)

target_include_directories( ${PROJECT_NAME} PRIVATE ${Boost_INCLUDE_DIRS} )

target_link_libraries( ${PROJECT_NAME}
    PRIVATE
        DBCW
        DA
        PostgreSQL::PostgreSQL
)

add_test_( ${PROJECT_NAME} )