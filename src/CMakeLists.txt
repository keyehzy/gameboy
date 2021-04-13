cmake_minimum_required(VERSION 3.12)

add_executable(
  gameboy
  gameboy.c
)
target_link_libraries(gameboy PRIVATE gameboy-lib)

add_library(
  gameboy-lib
  cpu.c
  disassembler.c
)
target_include_directories(gameboy-lib PUBLIC .)
