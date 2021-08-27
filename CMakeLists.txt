cmake_minimum_required(VERSION 3.18)
set(CMAKE_TOOLCHAIN_FILE "./vcpkg/scripts/buildsystems/vcpkg.cmake")

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

find_package(SFML 2.5.1 COMPONENTS graphics REQUIRED)
find_package(range-v3 REQUIRED)

if(UNIX AND NOT APPLE)
    # workaround for missing opengl dependency in SFML CMake (https://github.com/microsoft/vcpkg/issues/10949)
    set(EXTRA_LIBS GL)
endif()

target_link_libraries(tank_bot_fight_lib PUBLIC sfml-graphics pthread ${EXTRA_LIBS})
target_link_libraries(tank_bot_fight PRIVATE tank_bot_fight_lib sfml-graphics)

add_subdirectory(test)