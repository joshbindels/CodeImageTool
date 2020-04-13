#cmake_minimum_required(VERSION 3.1)

#set(CMAKE_CXX_STANDARD 11)
#set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
#set(CMAKE_MODULE_PATH /usr/local/Cellar/opencv/4.2.0_3/lib/cmake/opencv4)
#SET(OpenCV_DIR /usr/local/Cellar/opencv/4.2.0_3/lib/cmake/opencv4)
#project(CodeImageTool)

#add_executable(CodeImageTool src/main.cpp)

#target_link_libraries(CodeImageTool ${OpenCV_LIBS} )
#target_include_directories(CodeImageTool PUBLIC "include")
#target_include_directories(CodeImageTool PUBLIC "src")

cmake_minimum_required(VERSION 3.10)

project(CodeImageTool VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

find_package(OpenCV REQUIRED)

add_executable(CodeImageTool src/main.cpp)

target_link_libraries(CodeImageTool ${OpenCV_LIBS})

target_include_directories(CodeImageTool PUBLIC
                            "include"
                            "/usr/local/Cellar/opencv/4.3.0/include/opencv4"
                            )

