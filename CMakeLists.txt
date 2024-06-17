cmake_minimum_required(VERSION 3.28)
project(Projekt_MS_Programowanie2)

set(CMAKE_CXX_STANDARD 14)

find_package(SQLite3)

add_executable(Projekt_MS_Programowanie2
        Wszystkie_kody/poczotek.cpp
        Wszystkie_kody/laczenie_z_sql.cpp
        Wszystkie_kody/sqlite3.c
        #Wszystkie_kody/sqlite3.lib
)


