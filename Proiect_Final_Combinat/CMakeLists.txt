cmake_minimum_required(VERSION 3.15)
project(RezervareSali)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(RezervareSali
        main.cpp
        Sala.cpp
        Rezervare.cpp
        GestionarSali.cpp
        GestionarRezervari.cpp
        # Repository.h si Utils.h sunt header-only (nu au .cpp)
)
