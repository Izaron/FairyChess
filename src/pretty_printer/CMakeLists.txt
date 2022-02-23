add_library(pretty_printer pretty_printer.cc)

target_include_directories(pretty_printer INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

list(APPEND LIBS board)
target_link_libraries(pretty_printer PUBLIC ${LIBS})

enable_testing()

add_executable(
    pretty_printer_test
    pretty_printer_ut.cc
)

target_link_libraries(
    pretty_printer_test
    gtest_main
    boards_assembler
    pretty_printer
)

include(GoogleTest)
gtest_discover_tests(pretty_printer_test)
