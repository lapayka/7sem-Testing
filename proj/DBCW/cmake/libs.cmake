if ( WIN32 )
    set ( LIB_EXT lib )
elseif ( UNIX )
    set ( LIB_EXT a )
endif ()

#### libpq ####

find_package(OpenSSL REQUIRED)

find_package(PostgreSQL REQUIRED)

#### oatpp ####

find_package(oatpp REQUIRED)
find_package(oatpp-swagger REQUIRED)

#### jsoncpp ###

find_package(jsoncpp REQUIRED)

#### jwt ####

find_path(JWT_CPP_INCLUDE_DIRS "jwt-cpp/base.h" REQUIRED)

add_library( jwt INTERFACE IMPORTED)

target_include_directories( jwt SYSTEM INTERFACE "${JWT_CPP_INCLUDE_DIRS}" )


################

find_package( Boost REQUIRED)
