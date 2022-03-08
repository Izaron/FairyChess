add_library(
    fairy_pieces
    amazon_piece.cc
    anti_pawn_piece.cc
    atomic_pieces.cc
    champion_piece.cc
    dragon_piece.cc
    dummy_piece.cc
    empress_piece.cc
    fool_piece.cc
    grasshopper_piece.cc
    knight_king_piece.cc
    mann_piece.cc
    nuclear_missile_piece.cc
    princess_piece.cc
    really_big_board_pawn_piece.cc
    unicorn_piece.cc
    wizard_piece.cc
    zebra_piece.cc
)

target_include_directories(fairy_pieces INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

list(APPEND LIBS piece evaluator)
target_link_libraries(fairy_pieces PUBLIC ${LIBS})

enable_testing()

add_executable(
    fairy_pieces_test
    amazon_piece_ut.cc
    anti_pawn_piece_ut.cc
    atomic_pieces_ut.cc
    champion_piece_ut.cc
    dragon_piece_ut.cc
    empress_piece_ut.cc
    fool_piece_ut.cc
    grasshopper_piece_ut.cc
    knight_king_piece_ut.cc
    mann_piece_ut.cc
    nuclear_missile_piece_ut.cc
    princess_piece_ut.cc
    unicorn_piece_ut.cc
    wizard_piece_ut.cc
    zebra_piece_ut.cc
)

target_link_libraries(
    fairy_pieces_test
    gtest_main
    vanilla_pieces
    fairy_pieces
    pretty_printer
    minimax
    testing
)

include(GoogleTest)
gtest_discover_tests(fairy_pieces_test)
