add_library(Game Game.cpp)

target_include_directories(Game
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_PRINT_SOURCE_DIR}
)
