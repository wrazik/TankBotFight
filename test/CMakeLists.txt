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
  BackgroundTextureNameTests.cpp
  FillVecTests.cpp
  RandomTests.cpp
  TankTests.cpp
  TextureStoreTests.cpp
  SquareRootEngineTests.cpp
  TestUtility.cpp
  UtilityTests.cpp
  TracesHandlerTests.cpp
  TankPartTests.cpp
  TankTowerTests.cpp
)

target_include_directories(run_tests PRIVATE
    ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(
  run_tests
  gmock
  gtest_main
  sfml-graphics
  tank_bot_fight_lib
  range-v3::range-v3
  sfml-audio
)

include(GoogleTest)

gtest_discover_tests(run_tests)
