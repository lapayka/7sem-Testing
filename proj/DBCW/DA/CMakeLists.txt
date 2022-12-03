add_subdirectory( UnitTesting )
add_subdirectory( IntegrationTesting )

set ( PROJECT_NAME DA )

project ( ${PROJECT_NAME} CXX )

set ( Source_Files
    ConConfig.cpp
    PgAlbumRepository.cpp
    PgMusRepository.cpp
    PgPlaylistRepository.cpp
    PgTablesRepository.cpp
)

set ( Header_Files 
    AdminConnect.h
    ArtistConnect.h
    ConConfig.h
    IPgConnect.h
    PgAlbumRepository.h
    PgArtistRepository.h
    PgGraphRepository.h
    PgMusRepository.h
    PgPlaylistRepository.h
    PgTablesRepository.h
    PgUserRepo.h
    stUserConnect.h
)

set ( all_sources ${Source_Files} ${Header_Files} )

add_library( ${PROJECT_NAME} STATIC ${all_sources} )

target_include_directories( ${PROJECT_NAME} INTERFACE .)

target_link_libraries( ${PROJECT_NAME}
    PRIVATE
        PostgreSQL::PostgreSQL
    PUBLIC
        DBCW
)
