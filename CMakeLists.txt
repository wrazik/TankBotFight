cmake_minimum_required(VERSION 3.18)
project(TankBotFight)
set(CMAKE_CXX_STANDARD 20)

include(CTest)


add_library(tank_bot_fight_lib STATIC
    src/background/Background.cpp
    src/background/BackgroundTextureName.cpp
    src/background/Ground.cpp
    src/background/RoadGenerator.cpp
    src/background/SurfaceGenerator.cpp
    src/Board.cpp
    src/KeyboardController.cpp
    src/Missle.cpp
    src/Tank.cpp
    src/TextureStore.cpp
    src/Obstacle.cpp
    src/Random.cpp
)

target_include_directories(tank_bot_fight_lib PRIVATE src)

add_executable(tank_bot_fight 
    src/main.cpp
)

if(MSVC)
    target_compile_options(tank_bot_fight PRIVATE /W3 /WX /O2)
else()
    target_compile_options(tank_bot_fight PRIVATE -Wall -pedantic -Werror -Wextra -O3)
endif()

target_include_directories(tank_bot_fight PRIVATE src)

if (${APPLE})
    target_include_directories(tank_bot_fight PRIVATE /usr/local/Cellar/sfml/2.5.1_1/include)
    target_include_directories(tank_bot_fight_lib PRIVATE /usr/local/Cellar/sfml/2.5.1_1/include)
endif()


find_package(SFML 2.5.1 COMPONENTS graphics REQUIRED)
target_link_libraries(tank_bot_fight sfml-graphics pthread tank_bot_fight_lib)

add_subdirectory(${CMAKE_SOURCE_DIR}/lib/range-v3)

add_subdirectory(test)