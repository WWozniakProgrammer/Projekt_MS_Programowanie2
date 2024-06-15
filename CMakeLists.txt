cmake_minimum_required(VERSION 3.28)
project(Projekt_MS_Programowanie2)

set(CMAKE_CXX_STANDARD 14)

include_directories(Wszystkie_kody)

add_executable(Projekt_MS_Programowanie2
        Wszystkie_kody/poczotek.cpp
        Wszystkie_kody/screaper_py.cpp
        Wszystkie_kody/screaper_py.h)
