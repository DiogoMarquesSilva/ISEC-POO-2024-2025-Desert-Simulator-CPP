cmake_minimum_required(VERSION 3.27)
project(tp)

set(CMAKE_CXX_STANDARD 26)

add_executable(tp main.cpp
        Simulador.h
        Simulador.cpp
        Item.h
        Item.cpp
        Cidade.h
        Cidade.cpp
        Caravana.h
        Caravana.cpp
        Entidade.h
        Entidade.cpp
        Buffer.h
        Buffer.cpp
        Global.h
        Militar.h
        Militar.cpp
        Barbara.h
        Barbara.cpp
        Comercio.h
        Comercio.cpp
        Utilizador.h
        Utilizador.cpp
        Parametros.h
        Parametros.cpp
        Excecoes.h
        Excecoes.cpp
        PaiNatal.h
        PaiNatal.cpp)
