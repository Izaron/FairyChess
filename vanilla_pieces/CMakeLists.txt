add_library(
    vanilla_pieces
    bishop_piece.cc
    knight_piece.cc
    pawn_piece.cc
    queen_piece.cc
    rook_piece.cc
)

target_include_directories(vanilla_pieces INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

list(APPEND LIBS piece)
target_link_libraries(vanilla_pieces PUBLIC ${LIBS})

enable_testing()

add_executable(
    vanilla_pieces_test
    bishop_piece_ut.cc
    knight_piece_ut.cc
    pawn_piece_ut.cc
    queen_piece_ut.cc
    rook_piece_ut.cc
)

target_link_libraries(
    vanilla_pieces_test
    gtest_main
    vanilla_pieces
    fairy_pieces
    pretty_printer
    testing
)

include(GoogleTest)
gtest_discover_tests(vanilla_pieces_test)
