add_library(boards_assembler boards_assembler.cc)

target_include_directories(boards_assembler INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

list(APPEND LIBS board vanilla_pieces)
target_link_libraries(boards_assembler PUBLIC ${LIBS})
