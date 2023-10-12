cmake_minimum_required(VERSION 3.18)
set(CMAKE_TOOLCHAIN_FILE "./vcpkg/scripts/buildsystems/vcpkg.cmake")

project(TankBotFight)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

include(CTest)
include(clang-tidy)

option(ENABLE_CLANG_TIDY "Enables 'make tidy' command to run clang-tidy checks"
       OFF)
set(CLANG_TIDY_VERSION
    "12"
    CACHE STRING "Clang tidy version to run checks")

if(ENABLE_CLANG_TIDY)
  add_tidy_target(
    ${CLANG_TIDY_VERSION}
    FILES
    ${CMAKE_SOURCE_DIR}/src/*
    ${CMAKE_SOURCE_DIR}/src/background/*
    ${CMAKE_SOURCE_DIR}/src/Controllers/*
    ${CMAKE_SOURCE_DIR}/src/Tank/*
    ${CMAKE_SOURCE_DIR}/src/Players/*)
endif()

add_library(
  tank_bot_fight_lib STATIC
  src/background/Background.cpp
  src/background/BackgroundTextureName.cpp
  src/background/Ground.cpp
  src/background/RoadGenerator.cpp
  src/background/SurfaceGenerator.cpp
  src/Board.cpp
  src/Controllers/KeyboardController.cpp
  src/Controllers/DummyController.cpp
  src/Missle.cpp
  src/Tank/Tank.cpp
  src/Tank/TankFactory.cpp
  src/Tank/TankPart.cpp
  src/Tank/TankTower.cpp
  src/Tank/TankHealthBar.cpp
  src/TextureStore.cpp
  src/Random.cpp
  src/SquareRootEngine.cpp
  src/TracesHandler.cpp
  src/Trace.cpp
  src/Players/DummyPlayer.cpp
  src/Players/KeyboardPlayer.cpp
  src/Sound.cpp src/Animation.cpp src/Animation.hpp)

target_include_directories(tank_bot_fight_lib PRIVATE src)

add_executable(tank_bot_fight src/main.cpp)

if(MSVC)
  target_compile_options(tank_bot_fight PRIVATE /W3 /WX
                                                $<$<CONFIG:Release>:/O2>)
else()
  target_compile_options(tank_bot_fight PRIVATE -Wall -pedantic -Werror -Wextra
                                                -O3)
endif()

target_include_directories(tank_bot_fight PRIVATE src)

find_package(
  SFML 2.5.1
  COMPONENTS graphics audio
  REQUIRED)
find_package(range-v3 REQUIRED)
find_package(Microsoft.GSL CONFIG REQUIRED)

target_link_libraries(tank_bot_fight_lib PUBLIC sfml-graphics ${EXTRA_LIBS}
                                                Microsoft.GSL::GSL)
target_link_libraries(tank_bot_fight PRIVATE tank_bot_fight_lib sfml-graphics sfml-audio)

add_subdirectory(test)
