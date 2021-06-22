cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 20)
enable_testing()

include(CTest)
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(run_tests
  TankTest.cpp
  ${CMAKE_SOURCE_DIR}/src/Background.cpp
  ${CMAKE_SOURCE_DIR}/src/Board.cpp
  ${CMAKE_SOURCE_DIR}/src/Ground.cpp
  ${CMAKE_SOURCE_DIR}/src/KeyboardController.cpp
  ${CMAKE_SOURCE_DIR}/src/Obstacle.cpp
  ${CMAKE_SOURCE_DIR}/src/Tank.cpp
  ${CMAKE_SOURCE_DIR}/src/TextureStore.cpp
)

target_include_directories(run_tests PRIVATE
    ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(
  run_tests
  gtest_main
  sfml-graphics
)

include(GoogleTest)

gtest_discover_tests(run_tests)
