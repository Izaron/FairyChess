add_library(vanilla_pieces pawn.cc)

target_include_directories(vanilla_pieces INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

list(APPEND LIBS piece)
target_link_libraries(vanilla_pieces PUBLIC ${LIBS})

enable_testing()

add_executable(
    vanilla_pieces_test
    pawn_ut.cc
)

target_link_libraries(
    vanilla_pieces_test
    gtest_main
    vanilla_pieces
    pretty_printer
    testing
)

include(GoogleTest)
gtest_discover_tests(vanilla_pieces_test)
