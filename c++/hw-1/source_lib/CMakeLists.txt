project(source_lib)

set(HEADER_FILES
        soft_config.h
        )

set(SOURCE_FILES
        config_sort.c
        config_sort.h io_manager.c io_manager.h)

add_library(source_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})