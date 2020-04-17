cmake_minimum_required(VERSION 3.10)

project(CodeImageTool VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

find_package(OpenCV REQUIRED)

file(GLOB SRC_FILES src/*.cpp)
add_executable(CodeImageTool ${SRC_FILES})

target_link_libraries(CodeImageTool ${OpenCV_LIBS})

target_include_directories(CodeImageTool PRIVATE
                            "include"
                            "/usr/local/Cellar/opencv/4.3.0/include/opencv4"
                            )

enable_testing()
find_package(GTest REQUIRED)
project(CodeImageToolTest VERSION 1.0)

file(GLOB TEST_FILES src/*.cpp test/*.cpp)
list(REMOVE_ITEM TEST_FILES ${CMAKE_SOURCE_DIR}/src/main.cpp)

add_executable(CodeImageToolTest ${TEST_FILES})
target_include_directories(CodeImageToolTest PRIVATE "include")
target_link_libraries(CodeImageToolTest GTest::GTest GTest::Main)

