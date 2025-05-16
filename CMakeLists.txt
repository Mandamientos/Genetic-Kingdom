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
    src/states/gameState/entities/castle.cpp
    src/states/gameState/entities/tower.cpp
    src/states/gameState/entities/archerTower.cpp
    src/states/gameState/entities/mageTower.cpp
    src/states/gameState/entities/archMageTower.cpp
    src/states/gameState/enemies/Enemy.cpp
    src/states/gameState/enemies/Ogre.cpp
    src/states/gameState/enemies/EnemyManager.cpp
    src/states/gameState/enemies/DarkElf.cpp
    src/states/gameState/enemies/Harpy.cpp
    src/states/gameState/enemies/Mercenary.cpp
    src/states/gameState/map/aStar.cpp 
    src/states/gameState/genetics/GeneticManager.cpp
)

set(HEADERS
    src/gameState.hpp
    src/gameStateManager.hpp
    src/states/mainMenu/mainMenu.hpp
    src/states/gameState/playState.hpp
    src/states/gameState/map/tilemap.hpp
    src/states/gameState/misc/player.hpp
    src/states/gameState/misc/animateSprite.hpp
    src/states/gameState/entities/castle.hpp
    src/states/gameState/entities/tower.hpp
    src/states/gameState/entities/archerTower.hpp
    src/states/gameState/entities/mageTower.hpp
    src/states/gameState/entities/archMageTower.hpp
    src/states/gameState/entities/towerFactory.hpp
    src/states/gameState/enemies/Enemy.hpp
    src/states/gameState/enemies/Ogre.hpp
    src/states/gameState/enemies/EnemyManager.hpp
    src/states/gameState/enemies/DarkElf.hpp
    src/states/gameState/enemies/Harpy.hpp
    src/states/gameState/enemies/Mercenary.hpp
    src/states/gameState/map/aStar.hpp
    src/states/gameState/genetics/GeneticManager.hpp
    src/states/gameState/genetics/EnemyGenome.hpp
    src/states/gameState/enemies/EnemyType.hpp
)

include_directories(
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/src/states
    ${PROJECT_SOURCE_DIR}/src/states/mainMenu
    ${PROJECT_SOURCE_DIR}/src/states/gameState
    ${PROJECT_SOURCE_DIR}/src/states/gameState/map
    ${PROJECT_SOURCE_DIR}/src/states/gameState/misc
    ${PROJECT_SOURCE_DIR}/src/states/gameState/enemies
    ${PROJECT_SOURCE_DIR}/src/states/gameState/entities
)

file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})

add_executable(Genetic-Kingdom ${SOURCES} ${HEADERS})

target_link_libraries(Genetic-Kingdom
    sfml-graphics
    sfml-window
    sfml-system
    sfml-audio
)
