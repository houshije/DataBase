cmake_minimum_required(VERSION 3.5.0)

project(MD5 C)

include_directories(.)

set(SRCS
    md5.c
)

add_library(md5 SHARED ${SRCS})
add_library(md5_static STATIC ${SRCS})
set_target_properties(md5_static PROPERTIES OUTPUT_NAME "md5")
