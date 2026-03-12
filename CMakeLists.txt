cmake_minimum_required(VERSION 3.10)
project(cgeneric C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Architecture Detection
if(CMAKE_SYSTEM_PROCESSOR MATCHES "aarch64|arm64|ARM64")
    set(TARGET_ARCH "arm64")
    if(APPLE)
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -arch arm64")
    else()
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -march=armv8-a")
    endif()
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64|amd64")
    set(TARGET_ARCH "x86_64")
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "i386|i686|x86")
    set(TARGET_ARCH "x86")
endif()

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror -g3")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-gnu-statement-expression")

include_directories(${CMAKE_SOURCE_DIR}/include)

set(LIB_PREFIX "cgeneric")

file(GLOB SOURCES "${CMAKE_SOURCE_DIR}/source/*.c")

add_library(${LIB_PREFIX} STATIC ${SOURCES})

foreach(src ${SOURCES})
    get_filename_component(name ${src} NAME_WE)
    add_library(${LIB_PREFIX}_lib_${name} STATIC ${src})
    set_target_properties(${LIB_PREFIX}_lib_${name} PROPERTIES
        OUTPUT_NAME "${LIB_PREFIX}_lib_${name}"
    )
endforeach()

install(TARGETS ${LIB_PREFIX}
    ARCHIVE DESTINATION lib
)
