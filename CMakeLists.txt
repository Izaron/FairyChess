cmake_minimum_required(VERSION 3.14)

project(fairy_chess VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(fairy_chess fairy_chess.cc)


# link libraries
add_subdirectory(bit_storage)
add_subdirectory(board)
add_subdirectory(boards_assembler)
add_subdirectory(evaluator)
add_subdirectory(piece)
add_subdirectory(vanilla_pieces)

list(APPEND EXTRA_LIBS bit_storage board boards_assembler evaluator piece vanilla_pieces)

target_link_libraries(fairy_chess PUBLIC ${EXTRA_LIBS})

# enable gtest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/c9461a9b55ba954df0489bab6420eb297bed846b.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()
