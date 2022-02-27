add_library(
    fairy_pieces
    amazon_piece.cc
    anti_pawn_piece.cc
    dummy_piece.cc
)

target_include_directories(fairy_pieces INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

list(APPEND LIBS piece)
target_link_libraries(fairy_pieces PUBLIC ${LIBS})

enable_testing()

add_executable(
    fairy_pieces_test
    amazon_piece_ut.cc
    anti_pawn_piece_ut.cc
)

target_link_libraries(
    fairy_pieces_test
    gtest_main
    vanilla_pieces
    fairy_pieces
    pretty_printer
    testing
)

include(GoogleTest)
gtest_discover_tests(fairy_pieces_test)
