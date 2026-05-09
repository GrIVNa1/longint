cmake_minimum_required(VERSION 3.20)   # или 3.10 – главное, не 4.2
project(longint)

set(CMAKE_CXX_STANDARD 14)

add_executable(longint
        main.cpp
        integer.cpp
        natural.cpp
        " rational.cpp"
        rational.h
        rational_struct.h
)