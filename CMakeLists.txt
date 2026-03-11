cmake_minimum_required(VERSION 3.10)
project(cgeneric C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror -g3")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-gnu-statement-expression")

include_directories(${CMAKE_SOURCE_DIR}/include)

set(LIB_PREFIX "cgeneric")

file(GLOB SOURCES "${CMAKE_SOURCE_DIR}/source/*.c")

add_library(${LIB_PREFIX} STATIC ${SOURCES})
add_library(${LIB_PREFIX}_shared SHARED ${SOURCES})
set_target_properties(${LIB_PREFIX} ${LIB_PREFIX}_shared PROPERTIES
    OUTPUT_NAME ${LIB_PREFIX}
)

foreach(src ${SOURCES})
    get_filename_component(name ${src} NAME_WE)
    add_library(${LIB_PREFIX}_lib_${name} STATIC ${src})
    add_library(${LIB_PREFIX}_lib_${name}_shared SHARED ${src})
    set_target_properties(${LIB_PREFIX}_lib_${name} PROPERTIES
        OUTPUT_NAME "${LIB_PREFIX}_lib_${name}"
    )
    set_target_properties(${LIB_PREFIX}_lib_${name}_shared PROPERTIES
        OUTPUT_NAME "${LIB_PREFIX}_lib_${name}"
    )
endforeach()

install(TARGETS ${LIB_PREFIX} ${LIB_PREFIX}_shared
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
)
