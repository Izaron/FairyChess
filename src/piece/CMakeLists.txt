add_library(piece piece.cc board_piece.cc piece_registry.cc piece_or_empty.cc)

target_include_directories(piece INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

list(APPEND LIBS bit_storage move_generator)
target_link_libraries(piece PUBLIC ${LIBS})

enable_testing()

add_executable(
    piece_test
    board_piece_ut.cc
)

target_link_libraries(
    piece_test
    gtest_main
    piece
)

include(GoogleTest)
gtest_discover_tests(piece_test)
