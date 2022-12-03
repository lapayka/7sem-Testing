set ( PROJECT_NAME DBCW )

project ( ${PROJECT_NAME} CXX )

set ( Source_Files
    Config.cpp
    Facade.cpp
    LoginException.cpp
    MusItem.cpp
)

set ( Header_Files 
    Config.h
    ConnectException.h
    Facade.h
    IAlbumsRepository.h
    IArtistRepository.h
    IConnect.h
    IGraphRepo.h
    IMusRepository.h
    IPlaylistRepository.h
    ITablesRepository.h
    IUserRepo.h
    LoginException.h
    MusItem.h
    PlstItem.h
)

set ( all_sources ${Source_Files} ${Header_Files} )

add_library( ${PROJECT_NAME} STATIC ${all_sources} )

target_include_directories( ${PROJECT_NAME} INTERFACE . )

