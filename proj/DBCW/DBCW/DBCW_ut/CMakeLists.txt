set (PROJECT_NAME DBCW_ut)
project ( ${PROJECT_NAME} CXX )

add_executable( ${PROJECT_NAME} Test.cpp )

target_link_libraries( ${PROJECT_NAME} 
    PRIVATE
        DBCW        
)

enable_testing()
add_test( NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME} )