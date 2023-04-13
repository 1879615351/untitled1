cmake_minimum_required(VERSION 3.24)
project(untitled1)

set(CMAKE_CXX_STANDARD 17)
set(concurrentqueue_INCLUDE_DIRS "E:/opt/vcpkg/installed/x64-windows/include/concurrentqueue")
include_directories(${concurrentqueue_INCLUDE_DIRS})
add_executable(untitled1 main.cpp pin.hpp Recorder.cpp Recorder.h)
