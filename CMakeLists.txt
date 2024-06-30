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
        "src/piece.cpp"
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

add_executable(square_tests "test/square_tests.cpp")
target_include_directories(square_tests PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(square_tests PRIVATE ${Boost_LIBRARIES})
target_link_libraries(square_tests PRIVATE bomchess)

add_executable(color_tests "test/color_tests.cpp")
target_include_directories(color_tests PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(color_tests PRIVATE ${Boost_LIBRARIES})
target_link_libraries(color_tests PRIVATE bomchess)

add_executable(piece_tests "test/piece_tests.cpp")
target_include_directories(piece_tests PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(piece_tests PRIVATE ${Boost_LIBRARIES})
target_link_libraries(piece_tests PRIVATE bomchess)

enable_testing()
add_test(NAME square_tests COMMAND square_tests)
add_test(NAME color_tests COMMAND color_tests)
add_test(NAME piece_tests COMMAND piece_tests)

install(TARGETS bomchess FILE_SET HEADERS)
