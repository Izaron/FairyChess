add_library(boards_assembler boards_assembler.cc)

target_include_directories(boards_assembler INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

list(APPEND LIBS board vanilla_pieces fairy_pieces)
target_link_libraries(boards_assembler PUBLIC ${LIBS})

enable_testing()

add_executable(
    boards_assembler_test
    boards_assembler_ut.cc
)

target_link_libraries(
    boards_assembler_test
    gtest_main
    boards_assembler
    pretty_printer
)

include(GoogleTest)
gtest_discover_tests(boards_assembler_test)
