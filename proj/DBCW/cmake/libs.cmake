if ( WIN32 )
    set ( LIB_EXT lib )
elseif ( UNIX )
    set ( LIB_EXT a )
endif ()

set ( LIBS_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/libs )

#### libpq ####

set (LIBPQ_ROOT ${LIBS_ROOT}/libpq )

add_library( libpq INTERFACE IMPORTED)

if (WIN32)
	target_include_directories ( libpq INTERFACE ${LIBPQ_ROOT}/include )
	target_link_libraries ( libpq INTERFACE "${LIBPQ_ROOT}/bin/libpq.${LIB_EXT}")
else ()
    target_include_directories ( libpq SYSTEM INTERFACE "/usr/include/postgresql" )
    target_link_libraries ( libpq INTERFACE  "/usr/lib/x86_64-linux-gnu/libcrypt.so.1.1.0" "/usr/lib/x86_64-linux-gnu/libpq.so" )
endif()

#find_package(PostgreSQL REQUIRED)

find_package( OpenSSL REQUIRED )

#### oatpp ####

find_package(oatpp REQUIRED)
find_package(oatpp-swagger REQUIRED)

#### jsoncpp ###

find_package(jsoncpp REQUIRED)

#### jwt ####

find_path(JWT_CPP_INCLUDE_DIRS NAMES "jwt-cpp/base.h" PATHS "C:/src/vcpkg/installed/x86-windows/include" REQUIRED)

add_library( jwt INTERFACE IMPORTED)

target_include_directories( jwt SYSTEM INTERFACE "${JWT_CPP_INCLUDE_DIRS}" )


################

