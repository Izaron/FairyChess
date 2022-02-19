add_library(board board.cc)

target_include_directories(board INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

list(APPEND LIBS piece)
target_link_libraries(board PUBLIC ${LIBS})

enable_testing()

add_executable(
    board_test
    board_ut.cc
)

target_link_libraries(
    board_test
    gtest_main
    board
    boards_assembler  # the test will use the vanilla board
)

include(GoogleTest)
gtest_discover_tests(board_test)
