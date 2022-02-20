add_library(
    minimax
    minimax.cc
)

target_include_directories(minimax INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

list(APPEND LIBS move_generator evaluator)
target_link_libraries(minimax PUBLIC ${LIBS})
