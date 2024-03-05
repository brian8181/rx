# File Name:  rx/src/CMakeLists.txt
# Build Date: Mon Mar  4 09:11:39 AM CST 2024
# Version:    0.1.0

cmake_minimum_required(VERSION 3.2)
project(regexer CXX)

# create executable
add_executable(rx
main.cpp
rx.cpp
)