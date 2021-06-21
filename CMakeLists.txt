cmake_minimum_required(VERSION 3.18)
project(TankBotFight)
set(CMAKE_CXX_STANDARD 20)

include(CTest)

set(SFML_VERSION "2.5.1")

find_package(SFML 2.5.1 COMPONENTS graphics REQUIRED)

add_executable(tank_bot_fight 
    src/main.cpp 
    src/Background.cpp
    src/Board.cpp
    src/Ground.cpp
    src/Tank.cpp 
    src/TextureStore.cpp 
    src/Obstacle.cpp)

if(MSVC)
    target_compile_options(tank_bot_fight PRIVATE /W3 /WX /O2)
else()
    target_compile_options(tank_bot_fight PRIVATE -Wall -pedantic -Werror -Wextra -O3)
endif()

target_include_directories(tank_bot_fight PRIVATE src 
    ${CMAKE_CURRENT_BINARY_DIR}/proto)

target_link_libraries(tank_bot_fight sfml-graphics pthread)

add_subdirectory(test)
