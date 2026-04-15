cmake_minimum_required(VERSION 3.15)

project(InfinityBattle)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_PREFIX_PATH ${CMAKE_SOURCE_DIR}/external)

find_package(SDL3 REQUIRED)
find_package(SDL3_image REQUIRED)
find_package(SDL3_ttf REQUIRED)
find_package(SDL3_mixer REQUIRED)
file(GLOB HEADERS "include/*.h")
file(GLOB SOURCES "source/*.cpp")
set(ALL_SOURCES ${HEADERS} ${SOURCES})
add_executable(InfinityBattle ${ALL_SOURCES})

target_include_directories(InfinityBattle PRIVATE 
include
external/SDL3/include
external/SDL3_image/include
external/SDL3_ttf/include
external/SDL3_mixer/include
)

target_link_libraries(InfinityBattle
    SDL3::SDL3
    SDL3_image::SDL3_image
    SDL3_mixer::SDL3_mixer
    SDL3_ttf::SDL3_ttf
)
