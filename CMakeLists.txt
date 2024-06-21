cmake_minimum_required(VERSION 3.27)

set(CMAKE_CXX_STANDARD 23)

project(bomchess)
include_directories(include)

set(Boost_USE_STATIC_LIBS ON)
find_package(Boost 1.83.0 REQUIRED COMPONENTS unit_test_framework)

add_library(bomchess)
target_include_directories(bomchess PRIVATE ${Boost_INCLUDE_DIRS})
target_sources(bomchess PRIVATE
    "src/board.cpp"
    "src/boardbuilder.cpp"
    "src/game.cpp"
    "src/move.cpp"
    "src/movegen.cpp"
    "src/square.cpp"

    PUBLIC FILE_SET HEADERS BASE_DIRS ${PROJECT_SOURCE_DIR}/include FILES
    "include/board.h"
    "include/boardbuilder.h"
    "include/color.h"
    "include/game.h"
    "include/move.h"
    "include/movegen.h"
    "include/piece.h"
    "include/position.h"
    "include/square.h"
)

add_executable(board_tests "test/board_tests.cpp")
target_include_directories(board_tests PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(board_tests PRIVATE ${Boost_LIBRARIES})
target_link_libraries(board_tests PRIVATE bomchess)

install(TARGETS bomchess FILE_SET HEADERS)
