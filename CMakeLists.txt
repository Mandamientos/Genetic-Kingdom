cmake_minimum_required(VERSION 3.10)
project(geneticKingdom)

set(CMAKE_CXX_STANDARD 17)

# Ruta a tu instalación de SFML
set(SFML_ROOT "/home/guillermo/SFML-3.0.0")

include_directories(${SFML_ROOT}/include)

link_directories(${SFML_ROOT}/lib)

add_executable(Genetic-Kingdom src/main.cpp)

target_link_libraries(Genetic-Kingdom
    sfml-graphics
    sfml-window
    sfml-system
)
