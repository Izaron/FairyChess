add_library(evaluator evaluator.cc)

target_include_directories(evaluator INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

list(APPEND LIBS board)
target_link_libraries(evaluator PUBLIC ${LIBS})

enable_testing()

add_executable(
    evaluator_test
    evaluator_ut.cc
)

target_link_libraries(
    evaluator_test
    gtest_main
    evaluator
    boards_assembler  # to evaluate default boards
)

include(GoogleTest)
gtest_discover_tests(evaluator_test)
