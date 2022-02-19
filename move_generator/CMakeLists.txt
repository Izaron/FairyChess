add_library(move_generator move_generator.cc)

target_include_directories(move_generator INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

list(APPEND LIBS board)
target_link_libraries(move_generator PUBLIC ${LIBS})

enable_testing()

add_executable(
    move_generator_test
    move_generator_ut.cc
)

target_link_libraries(
    move_generator_test
    gtest_main
    move_generator
    boards_assembler  # the test will check boards
)

include(GoogleTest)
gtest_discover_tests(move_generator_test)
