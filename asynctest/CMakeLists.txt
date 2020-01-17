cmake_minimum_required(VERSION 3.15)
project(asynctest)

set(CMAKE_CXX_STANDARD 14)

add_executable(asynctest main.cpp)

target_link_libraries(asynctest
  pthread)