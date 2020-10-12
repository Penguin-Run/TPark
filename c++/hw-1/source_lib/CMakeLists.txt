project(source_lib)

set(HEADER_FILES
        soft_config.h
        )

set(SOURCE_FILES
        source.c
        )

add_library(source_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})