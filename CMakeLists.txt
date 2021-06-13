cmake_minimum_required(VERSION 3.14)
project(TankBotFight)
set(CMAKE_CXX_STANDARD 20)

find_package(SFML 2.5 COMPONENTS graphics REQUIRED)

add_executable(tank_bot_fight 
    src/main.cpp 
    src/Tank.cpp 
    src/Obstacle.cpp)

target_compile_options(tank_bot_fight PUBLIC -Wall -Wpedantic -Werror)

target_include_directories(tank_bot_fight PRIVATE src)

target_link_libraries(tank_bot_fight sfml-graphics)

add_subdirectory(test)
