add_library(board board.cc)

target_include_directories(board INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

list(APPEND LIBS piece)
target_link_libraries(board PUBLIC ${LIBS})
