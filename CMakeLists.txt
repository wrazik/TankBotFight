cmake_minimum_required(VERSION 3.18)
project(TankBotFight)
set(CMAKE_CXX_STANDARD 20)

include(CTest)

set(SFML_VERSION "2.5.1")

find_package(SFML 2.5.1 COMPONENTS graphics REQUIRED)


add_library(tank_bot_fight_lib STATIC
    src/background/Background.cpp
    src/background/Ground.cpp
    src/background/RoadGenerator.cpp
    src/background/SurfaceGenerator.cpp
    src/Board.cpp
    src/KeyboardController.cpp
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

target_link_libraries(tank_bot_fight sfml-graphics pthread tank_bot_fight_lib)

add_subdirectory(test)
