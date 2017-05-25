cmake_minimum_required(VERSION 3.0)
project(dota_code)



SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 ")
add_executable(dota_code main.cpp csv.h)
target_link_libraries( dota_code pthread )
