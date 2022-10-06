cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(lab1 LANGUAGES CXX)
set(SOURCES main.cpp matrix.cpp head.h)
add_executable(lab1 ${SOURCES})
