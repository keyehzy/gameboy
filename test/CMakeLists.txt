cmake_minimum_required(VERSION 3.18)

add_executable(
  gameboy-test
  test-simple.cpp
)
target_include_directories(gameboy-test PRIVATE include)
target_link_libraries(
  gameboy-test
  PRIVATE
  gmock
  gmock_main
  gtest
  gameboy-lib
)

add_test(
  NAME gameboy-test
  COMMAND gameboy-test
)
