cmake_minimum_required(VERSION 3.14)

project(fairy_chess VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Ofast")

add_executable(fairy_chess fairy_chess.cc)


# add our libraries
add_subdirectory(bit_storage)
add_subdirectory(board)
add_subdirectory(boards_assembler)
add_subdirectory(evaluator)
add_subdirectory(move_generator)
add_subdirectory(piece)
add_subdirectory(pretty_printer)
add_subdirectory(testing)
add_subdirectory(vanilla_pieces)
add_subdirectory(fairy_pieces)
add_subdirectory(minimax)
add_subdirectory(zobrist_hashing)
add_subdirectory(graphics)

list(APPEND EXTRA_LIBS bit_storage board boards_assembler evaluator
                       move_generator piece pretty_printer vanilla_pieces
                       minimax graphics)

# add SFML libraries (for graphics)
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
list(APPEND EXTRA_LIBS sfml-graphics sfml-window sfml-system)


# link the executable
target_link_libraries(fairy_chess PUBLIC ${EXTRA_LIBS})


# enable gtest (for testing)
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/c9461a9b55ba954df0489bab6420eb297bed846b.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()
