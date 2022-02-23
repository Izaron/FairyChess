add_library(
    minimax
    minimax.cc
)

target_include_directories(minimax INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

list(APPEND LIBS move_generator evaluator pretty_printer zobrist_hashing)
target_link_libraries(minimax PUBLIC ${LIBS})

enable_testing()

add_executable(
    minimax_test
    minimax_ut.cc
)

target_link_libraries(
    minimax_test
    gtest_main
    minimax
    vanilla_pieces
    testing
)

include(GoogleTest)
gtest_discover_tests(minimax_test)
