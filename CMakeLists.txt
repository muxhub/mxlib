cmake_minimum_required(VERSION 3.13)
project(mxlib)

set(CMAKE_CXX_STANDARD 14)
set(SRC src)
set(INCLUDE mxlib)

set(HEADERS
        ${INCLUDE}/core/jiaotu.h
        ${INCLUDE}/core/datetime.h
        ${INCLUDE}/configure/simpleConfiguration.h
        ${INCLUDE}/io/file.h
        ${INCLUDE}/io/directory.h )

set(SRC
        ${SRC}/core/jiaotu.cpp
        ${SRC}/core/datetime.cpp
        ${SRC}/configure/simpleConfiguration.cpp
        ${SRC}/io/file.cpp
        ${SRC}/io/directory.cpp
        src/core/datetime.cpp)

add_library(mxlib ${HEADERS} ${SRC})

add_executable(tester main.cpp)
target_link_libraries(tester mxlib)
