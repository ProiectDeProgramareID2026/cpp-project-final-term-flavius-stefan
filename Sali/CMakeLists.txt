cmake_minimum_required(VERSION 3.15)
project(GestionareSali)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_executable(gestionare_sali
        main_sali.cpp
        Sala.cpp
        GestionarSali.cpp)
