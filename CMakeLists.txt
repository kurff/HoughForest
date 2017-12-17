cmake_minimum_required(VERSION 3.5)
project(Beta)
option(test "Build all tests." ON)
SET(CMAKE_C_COMPILER g++)
add_compile_options(-std=c++11)
include_directories(../  /usr/local/include)
link_directories(/usr/local/lib /usr/lib)


add_executable(main  main.cpp proto/configuration.pb.cc)

target_link_libraries(main  opencv_highgui opencv_core opencv_imgproc glog protobuf)