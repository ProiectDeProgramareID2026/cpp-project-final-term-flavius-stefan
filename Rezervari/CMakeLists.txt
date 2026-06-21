cmake_minimum_required(VERSION 3.15)
project(GestionareRezervari)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_executable(gestionare_rezervari
        main_rezervari.cpp
        Rezervare.cpp
        GestionarRezervari.cpp
        Sala.cpp            # modulul Persoanei A (dependinta)
        GestionarSali.cpp)
