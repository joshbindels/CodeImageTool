cmake_minimum_required(VERSION 3.10)

project(CodeImageTool VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

find_package(OpenCV REQUIRED)

file(GLOB SRC_FILES src/*.cpp)
add_executable(CodeImageTool ${SRC_FILES})

target_link_libraries(CodeImageTool ${OpenCV_LIBS})

target_include_directories(CodeImageTool PUBLIC
                            "include"
                            "/usr/local/Cellar/opencv/4.3.0/include/opencv4"
                            )

