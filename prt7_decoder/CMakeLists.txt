cmake_minimum_required(VERSION 3.10)
project(prt7_decoder)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(src/include)

add_executable(prt7_decoder
    src/main.cpp
)
