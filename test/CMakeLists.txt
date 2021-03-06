cmake_minimum_required(VERSION 3.5)
project(Beta)
option(test "Build all tests." ON)
SET(CMAKE_C_COMPILER g++)
add_compile_options(-std=c++11)
include_directories(../  /usr/include/freetype2)
link_directories(/usr/local/lib /usr/lib)


add_executable(test_fonts  test_fonts.cpp)

target_link_libraries(test_fonts freetype opencv_highgui opencv_core opencv_imgproc)

if (test)
enable_testing()
add_executable(test_data  test_data.cpp)
target_link_libraries(test_data gtest gtest_main glog opencv_highgui opencv_core opencv_imgproc protobuf)
add_test(NAME test_data COMMAND test_data)

add_executable(test_selector  test_selector.cpp)
target_link_libraries(test_selector gtest gtest_main glog opencv_highgui opencv_core opencv_imgproc)
add_test(NAME test_selector COMMAND random_generation)

add_executable(test_configure  test_configure.cpp ../proto/configuration.pb.cc)
target_link_libraries(test_configure gtest gtest_main glog protobuf opencv_highgui opencv_core opencv_imgproc)
add_test(NAME test_configure COMMAND readtxt)


add_executable(test_serialize  test_serialization.cpp ../proto/configuration.pb.cc)
target_link_libraries(test_serialize gtest gtest_main glog protobuf opencv_highgui opencv_core opencv_imgproc)
add_test(NAME test_serialize COMMAND savetxt)
endif()