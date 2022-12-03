set( PROJECT_NAME libpq_MOCK )

add_library( ${PROJECT_NAME} STATIC )

target_sources( ${PROJECT_NAME}
    PRIVATE
        libpq-fe.h
        libpq-fe.cpp
)