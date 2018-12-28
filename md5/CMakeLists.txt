cmake_minimum_required(VERSION 3.5.0)

project(Customer_MD5 CXX)

include_directories(.)

if (CMAKE_BUILD_TYPE MATCHES "Debug")
    add_definitions(-g)
    set(CMAKE_DEBUG_POSTFIX  "d")
else ()
    set(LIB_SUFFIX )
endif ()

set(SRCS
    md5.cpp
)

add_library(md5 SHARED ${SRCS})
add_library(md5_static STATIC ${SRCS})
set_target_properties(md5_static PROPERTIES OUTPUT_NAME "md5")
