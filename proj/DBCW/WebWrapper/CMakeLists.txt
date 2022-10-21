set ( PROJECT_NAME WebWrapper)

project ( ${PROJECT_NAME} CXX )


set ( Source_Files 
      jwtWrapper.cpp
      WebWrapper.cpp)

set ( Header_Files
      DTO.h
      ServerController.h
      ServerSettings.h
      Token.h
      PasCon.h
      WebWrapper.h
      jwtWrapper.h)

set ( all_sources ${Source_Files} ${Header_Files} )

add_library ( WebWrapper STATIC ${all_sources})

target_include_directories ( ${PROJECT_NAME} PRIVATE ../Interface ../DBCW )
target_compile_definitions ( ${PROJECT_NAME} 
      PUBLIC 
            "PATH_TO_CONFIG=\"${CMAKE_CURRENT_SOURCE_DIR}/AdminPas.txt\"" 
            "OATPP_SWAGGER_RES_PATH=\"${OATPP_BASE_DIR}/bin/oatpp-swagger/res\""
)

target_include_directories( ${PROJECT_NAME} PUBLIC ${oatpp_INCLUDE_DIRS} ${oatpp-swagger_INCLUDE_DIRS} )

target_link_libraries ( ${PROJECT_NAME} 
  PUBLIC
    oatpp::oatpp
    oatpp::oatpp-swagger
    jsoncpp_lib
    jwt
)
