cmake_minimum_required(VERSION 3.10)
project(geneticKingdom)

set(CMAKE_CXX_STANDARD 17)

set(SFML_ROOT "$ENV{HOME}/SFML-3.0.0")

include_directories(${SFML_ROOT}/include)

link_directories(${SFML_ROOT}/lib)

set(SOURCES
    src/main.cpp
    src/states/mainMenu/mainMenu.cpp
    src/states/gameState/playState.cpp
    src/states/gameState/map/tilemap.cpp
    src/states/gameState/misc/player.cpp
    src/states/gameState/misc/animateSprite.cpp
)

set(HEADERS
    src/gameState.hpp
    src/gameStateManager.hpp
    src/states/mainMenu/mainMenu.hpp
    src/states/gameState/playState.hpp
    src/states/gameState/map/tilemap.hpp
    src/states/gameState/misc/player.hpp
    src/states/gameState/misc/animateSprite.hpp
)

include_directories(
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/src/states
    ${PROJECT_SOURCE_DIR}/src/states/mainMenu
    ${PROJECT_SOURCE_DIR}/src/states/gameState
    ${PROJECT_SOURCE_DIR}/src/states/gameState/map
    ${PROJECT_SOURCE_DIR}/src/states/gameState/misc
)

file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})

add_executable(Genetic-Kingdom ${SOURCES} ${HEADERS})

target_link_libraries(Genetic-Kingdom
    sfml-graphics
    sfml-window
    sfml-system
)
